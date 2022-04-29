#ifndef __CLIENT_MANAGER_H__
#define __CLIENT_MANAGER_H__

#include <list>
#include <map>
#include <memory>

#include "server/server.h"
#include "server/net_enums.h"

#include "config.h"
#include "user_info.h"
#include "intl.h"
#include "chat_ui.h"

#include "scenes/scene_base.h"

#define HANDLE_SRV_MESSAGE(name, ...) handle_message(enums::enum_tag_t<server_message_type::name> __VA_OPT__(,) __VA_ARGS__)

class client_manager {
public:
    client_manager(sdl::window &window, boost::asio::io_context &ctx, const std::filesystem::path &base_path);
    ~client_manager();

    void refresh_layout();

    void render(sdl::renderer &renderer);

    void handle_event(const sdl::event &event);

    template<client_message_type E, typename ... Ts>
    void add_message(Ts && ... args) {
        if (m_con) {
            m_con->push_message(enums::enum_tag<E>, std::forward<Ts>(args) ...);
        }
    }

    void update_net();

    void connect(const std::string &host);
    void disconnect(const std::string &message = {});

    template<std::derived_from<scene_base> T, typename ... Ts>
    void switch_scene(Ts && ... args) {
        m_chat.disable();
        m_scene = std::make_unique<T>(this, std::forward<Ts>(args) ...);
        refresh_layout();
    }

    config &get_config() {
        return m_config;
    }

    sdl::window &get_window() {
        return m_window;
    }

    const std::filesystem::path &get_base_path() const { return m_base_path; }

    sdl::rect get_rect() const {
        sdl::rect rect{};
        SDL_GetWindowSize(m_window.get(), &rect.w, &rect.h);
        return rect;
    }

    int width() const { return get_rect().w; }
    int height() const { return get_rect().h; }

    int get_user_own_id() const { return m_user_own_id; }
    int get_lobby_owner_id() const { return m_lobby_owner_id; }

    bool start_listenserver();

    user_info *get_user_info(int id) {
        auto it = m_users.find(id);
        if (it != m_users.end()) {
            return &it->second;
        } else {
            return nullptr;
        }
    }

    void enable_chat();

    void add_chat_message(message_type type, const std::string &message);

private:
    void HANDLE_SRV_MESSAGE(client_accepted, const client_accepted_args &args);
    void HANDLE_SRV_MESSAGE(lobby_error, const std::string &message);
    void HANDLE_SRV_MESSAGE(lobby_update, const lobby_data &args);
    void HANDLE_SRV_MESSAGE(lobby_edited, const lobby_info &args);
    void HANDLE_SRV_MESSAGE(lobby_entered, const lobby_entered_args &args);
    void HANDLE_SRV_MESSAGE(lobby_add_user, const lobby_add_user_args &args);
    void HANDLE_SRV_MESSAGE(lobby_remove_user, const lobby_remove_user_args &args);
    void HANDLE_SRV_MESSAGE(lobby_chat, const lobby_chat_args &args);
    void HANDLE_SRV_MESSAGE(game_started, const banggame::game_options &options);
    void HANDLE_SRV_MESSAGE(game_update, const banggame::game_update &args);

private:
    sdl::window &m_window;

    std::filesystem::path m_base_path;
    config m_config;

    std::unique_ptr<scene_base> m_scene;

    chat_ui m_chat{this};

    int m_user_own_id = 0;
    int m_lobby_owner_id = 0;

private:
    boost::asio::io_context &m_ctx;

    using connection_type = net::connection<net::message_types<server_message, client_message, banggame::bang_header>>;
    connection_type::pointer m_con;

    boost::asio::basic_waitable_timer<std::chrono::system_clock> m_accept_timer;

    std::map<int, user_info> m_users;
    
    std::unique_ptr<bang_server> m_listenserver;

};

#endif