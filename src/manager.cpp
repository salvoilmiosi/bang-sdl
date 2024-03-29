#include "manager.h"

#include <sstream>
#include <iostream>
#include <charconv>

#include "net/options.h"

#include "media_pak.h"
#include "os_api.h"

#include "scenes/connect.h"
#include "scenes/loading.h"
#include "scenes/lobby_list.h"
#include "scenes/lobby.h"
#include "gamescene/game.h"
#include "net/git_version.h"

using namespace banggame;

client_manager::client_manager(sdl::window &window, sdl::renderer &renderer, const std::filesystem::path &base_path)
    : m_window(window)
    , m_renderer(renderer)
    , m_base_path(base_path)
{
    m_config.load();
    switch_scene<connect_scene>();
}

client_manager::~client_manager() {
    stop_listenserver();
    m_config.save();
}

void client_manager::on_open() {
    m_connection_open = true;

    m_accept_timer = accept_timeout;

    add_message<banggame::client_message_type::connect>(
        banggame::user_info {
            m_config.user_name,
            sdl::surface_to_image_pixels(m_config.profile_image_data)
        },
        get_user_own_id()
#ifdef HAVE_GIT_VERSION
        , std::string(net::server_commit_hash)
#endif
        );
}

void client_manager::on_close() {
    if (!m_connection_closed.exchange(true)) {
        switch_scene<connect_scene>();
    }
    if (m_connection_open.exchange(false)) {
        add_chat_message(message_type::server_log, _("ERROR_DISCONNECTED"));
    }
    m_accept_timer.reset();
}

void client_manager::on_message(const std::string &message) {
    try {
        auto server_msg = json::deserialize<server_message>(json::json::parse(message));
        try {
            enums::visit_indexed([&]<server_message_type E>(enums::enum_tag_t<E> tag, auto && ... args) {
                if constexpr (requires { handle_message(tag, args...); }) {
                    handle_message(tag, args...);
                }
                if (auto handler = dynamic_cast<message_handler<E> *>(m_scene.get())) {
                    handler->handle_message(tag, args...);
                } 
            }, server_msg);
        } catch (const std::exception &error) {
            add_chat_message(message_type::error, fmt::format("Error: {}", error.what()));
        }
    } catch (const std::exception &) {
        disconnect();
    }
}

void client_manager::connect(const std::string &host) {
    if (host.empty()) {
        add_chat_message(message_type::error, _("ERROR_NO_ADDRESS"));
    } else {
        m_connection_closed = false;
        net::wsconnection::connect(host);
        switch_scene<loading_scene>(_("CONNECTING_TO", host), host);
    }
}

void client_manager::disconnect() {
    stop_listenserver();
    net::wsconnection::disconnect();
}

void client_manager::refresh_layout() {
    m_scene->refresh_layout();

    m_chat.set_rect(sdl::rect{
        width() - 250,
        height() - 400,
        240,
        350
    });
}

static void render_tiled(sdl::renderer &renderer, sdl::texture_ref texture, const sdl::rect &dst_rect) {
    const sdl::rect src_rect = texture.get_rect();

    for (int y=dst_rect.y; y<=dst_rect.w + dst_rect.h + src_rect.h; y+=src_rect.h) {
        for (int x=dst_rect.x; x<=dst_rect.x + dst_rect.w + src_rect.w; x+=src_rect.w) {
            sdl::rect from = src_rect;
            sdl::rect to{x, y, src_rect.w, src_rect.h};
            if (to.x + to.w > dst_rect.x + dst_rect.w) {
                from.w = to.w = dst_rect.x + dst_rect.w - to.x;
            }
            if (to.y + to.h > dst_rect.y + dst_rect.h) {
                from.h = to.h = dst_rect.y + dst_rect.h - to.y;
            }
            SDL_RenderCopy(renderer.get(), texture.get(), &from, &to);
        }
    }
}

void client_manager::tick(duration_type time_elapsed) {
    poll();
    
    if (m_accept_timer && (*m_accept_timer -= time_elapsed) <= duration_type{}) {
        add_chat_message(message_type::error, _("ACCEPT_TIMEOUT_EXPIRED"));
        disconnect();
    }

    m_scene->tick(time_elapsed);
    m_chat.tick(time_elapsed);
}

void client_manager::render(sdl::renderer &renderer) {
    render_tiled(renderer, media_pak::get().texture_background, sdl::rect{0, 0, width(), height()});
    
    m_scene->render(renderer);
    m_chat.render(renderer);
}

void client_manager::handle_event(const sdl::event &event) {
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN && bool(event.key.keysym.mod & KMOD_ALT)) {
        Uint32 fullscreen = SDL_WINDOW_FULLSCREEN_DESKTOP;
        SDL_SetWindowFullscreen(m_window.get(), SDL_GetWindowFlags(m_window.get()) & fullscreen ? 0 : fullscreen);
    } else if (!widgets::event_handler::handle_events(event)) {
        m_scene->handle_event(event);
    }
}

void client_manager::enable_chat() {
    m_chat.enable();
}

void client_manager::add_chat_message(message_type type, const std::string &message) {
    m_chat.add_message(type, message);
}

std::filesystem::path client_manager::get_listenserver_path() const {
    std::filesystem::path server_path = m_base_path / "bangserver";
#ifdef _WIN32
    server_path.replace_extension(".exe");
#endif
    return server_path;
}

bool client_manager::is_listenserver_present() const {
#ifdef HAVE_GIT_VERSION
    std::atomic<bool> result = false;
    TinyProcessLib::Process proc(
        fmt::format("{} --version", get_listenserver_path().string()), "",
        [&](const char *bytes, size_t n) {
            std::string_view str{bytes, n};
            result.store(str.substr(0, str.find_first_of("\r\n")) == net::server_commit_hash);
        },
        nullptr
    );
    return proc.get_exit_status() == 0 && result.load();
#else
    return true;
#endif
}

void client_manager::start_listenserver() {
    switch_scene<loading_scene>(_("CREATING_SERVER"));
    m_connection_closed = false;

    if (!m_config.server_port) {
        m_config.server_port = default_server_port;
    }
    m_listenserver = std::make_unique<TinyProcessLib::Process>(
        fmt::format("{} {} {} {}",
            get_listenserver_path().string(),
            m_config.server_enable_cheats ? "--cheats" : "",
            m_config.server_verbose ? "--verbose" : "",
            m_config.server_port), "",
        [&](const char *bytes, size_t n) {
            std::string_view str{bytes, n};
            while (true) {
                size_t newline_pos = str.find_first_of("\r\n");
                auto line = str.substr(0, newline_pos);
                if (!line.empty()) {
                    add_chat_message(message_type::server_log, std::string(line));
                }
                if (line.starts_with("Server listening")) {
                    asio::post(get_executor(), [&]{
                        net::wsconnection::connect(fmt::format("ws://localhost:{}", m_config.server_port));
                    });
                }
                if (newline_pos == std::string_view::npos) break;
                str = str.substr(newline_pos + 1);
            }
        },
        [&, buffer = std::string()](const char *bytes, size_t n) mutable {
            buffer.append(bytes, n);
            while (true) {
                size_t newline_pos = buffer.find_first_of("\r\n");
                if (newline_pos == std::string_view::npos) break;
                if (newline_pos) {
                    add_chat_message(message_type::error, buffer.substr(0, newline_pos));
                }
                buffer.erase(0, newline_pos + 1);
            }
        });
    
    if (m_listenserver_thread.joinable()) {
        m_listenserver_thread.join();
    }
    m_listenserver_thread = std::thread([&]{
        m_listenserver->get_exit_status();
        asio::post(get_executor(), [&]{
            m_listenserver.reset();
            on_close();
        });
    });
}

void client_manager::stop_listenserver() {
    if (m_listenserver) {
#ifdef _WIN32
        m_listenserver->kill();
#else
        m_listenserver->signal(SIGTERM);
#endif
    }
    if (m_listenserver_thread.joinable()) {
        m_listenserver_thread.join();
    }
    m_listenserver.reset();
}

void client_manager::handle_message(SRV_TAG(ping)) {
    add_message<banggame::client_message_type::pong>();
}

void client_manager::client_accepted(const client_accepted_args &args, const std::string &address) {
    if (!address.empty() && !rn::contains(m_config.recent_servers, address)) {
        m_config.recent_servers.push_back(address);
    }
    m_accept_timer.reset();
    m_users.clear();
    m_config.user_id = args.user_id;
    switch_scene<lobby_list_scene>(m_lobbies);
}

void client_manager::handle_message(SRV_TAG(lobby_error), const std::string &message) {
    add_chat_message(message_type::error, _(message));
}

void client_manager::handle_message(SRV_TAG(lobby_entered), const lobby_entered_args &args) {
    switch_scene<lobby_scene>(args);
}

void client_manager::handle_message(SRV_TAG(lobby_owner), const user_id_args &args) {
    m_lobby_owner_id = args.user_id;
}

void client_manager::handle_message(SRV_TAG(lobby_add_user), const user_info_id_args &args) {
    auto it = rn::find(m_users, args.user_id, &id_user_info_pair::first);
    if (it == m_users.end()) {
        m_users.emplace_back(args.user_id, args.user);
        if (!args.is_read && args.user_id >= 0) {
            add_chat_message(message_type::server_log, _("GAME_USER_CONNECTED", args.user.name));
        }
    } else {
        *it = id_user_info_pair{ args.user_id, args.user };
    }
}

void client_manager::handle_message(SRV_TAG(lobby_remove_user), const user_id_args &args) {
    if (args.user_id == get_user_own_id()) {
        m_users.clear();
        switch_scene<lobby_list_scene>(m_lobbies);
    } else if (auto it = rn::find(m_users, args.user_id, &id_user_info_pair::first); it != m_users.end()) {
        if (args.user_id >= 0) {
            add_chat_message(message_type::server_log, _("GAME_USER_DISCONNECTED", it->second.name));
        }
        m_users.erase(it);
    }
}

void client_manager::handle_message(SRV_TAG(lobby_update), const lobby_data &args) {
    auto it = rn::find(m_lobbies, args.lobby_id, &lobby_data::lobby_id);
    if (it == m_lobbies.end()) {
        m_lobbies.emplace_back(args);
    } else {
        *it = args;
    }
}

void client_manager::handle_message(SRV_TAG(lobby_removed), const lobby_id_args &args) {
    auto it = rn::find(m_lobbies, args.lobby_id, &lobby_data::lobby_id);
    if (it != m_lobbies.end()) {
        m_lobbies.erase(it);
    }
}

void client_manager::handle_message(SRV_TAG(lobby_chat), const lobby_chat_args &args) {
    if (!args.is_read) {
        if (const banggame::user_info *info = get_user_info(args.user_id)) {
            add_chat_message(message_type::chat, fmt::format("{}: {}", info->name, args.message));
        } else {
            add_chat_message(message_type::chat, args.message);
        }
    }
}

void client_manager::handle_message(SRV_TAG(game_started)) {
    switch_scene<banggame::game_scene>();
}

sdl::texture client_manager::browse_propic() {
    if (auto value = os_api::open_file_dialog(
            _("BANG_TITLE"),
            m_config.profile_image,
            {
                {{"*.jpg","*.jpeg","*.png"}, _("DIALOG_IMAGE_FILES")},
                {{"*.*"}, _("DIALOG_ALL_FILES")}
            },
            &get_window()
        )) {
        try {
            m_config.profile_image = value->string();
            m_config.profile_image_data = widgets::profile_pic::scale_profile_image(sdl::surface(resource(*value)));
            return sdl::texture(get_renderer(), m_config.profile_image_data);
        } catch (const std::runtime_error &e) {
            add_chat_message(message_type::error, e.what());
        }
    }
    return {};
}

void client_manager::reset_propic() {
    m_config.profile_image.clear();
    m_config.profile_image_data.reset();
}

void client_manager::send_user_edit() {
    add_message<banggame::client_message_type::user_edit>(
        m_config.user_name,
        sdl::surface_to_image_pixels(m_config.profile_image_data)
    );
}