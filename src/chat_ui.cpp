#include "chat_ui.h"

#include "manager.h"

chat_ui::chat_ui(client_manager *parent)
    : parent(parent)
{
    m_chat_box.set_onenter([this](const std::string &value){ send_chat_message(value); });

    m_chat_box.disable();
}

void chat_ui::set_rect(const sdl::rect &rect) {
    m_rect = rect;

    int y = rect.y + rect.h - 35;
    for (auto it = m_messages.rbegin(); it != m_messages.rend(); ++it) {
        sdl::rect text_rect = it->text.get_rect();
        text_rect.x = m_rect.x;
        text_rect.y = y - text_rect.h;
        if (text_rect.y < m_rect.y) {
            m_messages.erase(m_messages.begin(), it.base());
            break;
        }
        it->text.set_rect(text_rect);

        y -= text_rect.h + widgets::default_text_list_yoffset;
    }

    m_chat_box.set_rect(sdl::rect{rect.x, rect.y + rect.h - 25, rect.w, 25});
}

void chat_ui::tick(duration_type time_elapsed) {
    for (auto it = m_messages.rbegin(); it != m_messages.rend(); ++it) {
        if (it->lifetime <= time_elapsed) {
            m_messages.erase(m_messages.begin(), it.base());
            break;
        }
        it->lifetime -= time_elapsed;
    }
    m_chat_box.tick(time_elapsed);
}

void chat_ui::render(sdl::renderer &renderer) {
    bool added = false;
    while (auto pair = m_pending_messages.pop_front()) {
        added = true;
        m_messages.emplace_back(widgets::stattext{pair->second, get_text_style(pair->first)}, widgets::chat_message_lifetime);
    }
    if (added) set_rect(m_rect);
    for (auto &msg : m_messages) {
        msg.text.render(renderer);
    }
    if (m_chat_box.enabled()) {
        m_chat_box.render(renderer);
    }
}

widgets::text_style chat_ui::get_text_style(message_type type) {
    switch (type) {
    case message_type::error:
        return {
            .text_color = widgets::error_text_color,
            .text_ptsize = widgets::error_text_ptsize,
            .wrap_length = m_rect.w
        };
    case message_type::server_log:
        return {
            .text_color = widgets::server_log_color,
            .text_ptsize = widgets::chat_text_ptsize,
            .wrap_length = m_rect.w
        };
    case message_type::chat:
    default:
        return {
            .text_ptsize = widgets::chat_text_ptsize,
            .wrap_length = m_rect.w
        };
    }
}

void chat_ui::add_message(message_type type, const std::string &message) {
    m_pending_messages.emplace_back(type, message);
}

void chat_ui::send_chat_message(const std::string &value) {
    if (!value.empty()) {
        parent->add_message<banggame::client_message_type::lobby_chat>(value);
        m_chat_box.clear();
    }
}

void chat_ui::enable() {
    m_chat_box.enable();
    widgets::event_handler::set_focus(&m_chat_box);
}

void chat_ui::disable() {
    m_chat_box.disable();
}

bool chat_ui::enabled() const {
    return m_chat_box.enabled();
}