#include "checkbox.h"

#include "../media_pak.h"

using namespace widgets;

checkbox::checkbox(const std::string &label, const button_style &style)
    : m_style(style)
    , m_text(label, style.text) {}

void checkbox::render(sdl::renderer &renderer) {
    renderer.set_draw_color([&]{
        switch (m_state) {
        case state_hover:   return m_style.hover_color;
        case state_down:    return m_style.down_color;
        case state_up:
        default:            return m_style.up_color;
        }
    }());
    renderer.fill_rect(m_checkbox_rect);

    renderer.set_draw_color(m_style.border_color);
    renderer.draw_rect(m_checkbox_rect);
    
    if (m_value) {
        media_pak::get().icon_checkbox.render(renderer, m_checkbox_rect);
    }

    m_text.render(renderer);
}

void checkbox::set_rect(const sdl::rect &rect) {
    m_border_rect = rect;
    m_checkbox_rect = sdl::rect{rect.x, rect.y, rect.h, rect.h};

    sdl::rect text_rect = m_text.get_rect();
    text_rect.x = m_checkbox_rect.x + m_checkbox_rect.w + 10;
    text_rect.y = m_checkbox_rect.y + (m_checkbox_rect.h - text_rect.h) / 2;
    m_text.set_rect(text_rect);
}

bool checkbox::handle_event(const sdl::event &event) {
    switch (event.type) {
    case SDL_MOUSEMOTION:
        if (sdl::point_in_rect(sdl::point{event.motion.x, event.motion.y}, m_checkbox_rect)) {
            if (m_state == state_up) {
                m_state = state_hover;
            }
        } else {
            if (m_state == state_hover) {
                m_state = state_up;
            }
        }
        break;
    case SDL_MOUSEBUTTONDOWN:
        if (event.button.button == SDL_BUTTON_LEFT
            && sdl::point_in_rect(sdl::point{event.motion.x, event.motion.y}, m_checkbox_rect)) {
            m_state = state_down;
            set_focus(this);
            return true;
        }
        break;
    case SDL_MOUSEBUTTONUP:
        if (event.button.button == SDL_BUTTON_LEFT
            && m_state == state_down) {
            if (sdl::point_in_rect(sdl::point{event.motion.x, event.motion.y}, m_checkbox_rect)) {
                m_state = state_hover;
                if (!m_locked) {
                    m_value = !m_value;
                    if (m_ontoggle) {
                        m_ontoggle(get_value());
                    }
                }
                return true;
            } else {
                m_state = state_up;
            }
        }
        break;
    };
    return false;
}