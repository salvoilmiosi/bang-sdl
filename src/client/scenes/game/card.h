#ifndef __CLIENT_CARD_H__
#define __CLIENT_CARD_H__

#include "common/card_enums.h"
#include "common/game_update.h"

#include "utils/sdl.h"

#include "sizes.h"

#include "../widgets/stattext.h"

#include <vector>
#include <list>

namespace banggame {

    struct card_textures {
    private:
        sdl::surface s_card_mask;

        sdl::texture s_main_deck;
        sdl::texture s_character;
        sdl::texture s_role;
        sdl::texture s_goldrush;

        sdl::texture s_card_border;

        sdl::texture s_cube;
        sdl::texture s_cube_border;

        sdl::texture s_gold;

        static inline card_textures *instance = nullptr;

        card_textures();

    public:
        static sdl::surface apply_card_mask(const sdl::surface &source);
        
        static const sdl::texture &main_deck() { return instance->s_main_deck; }
        static const sdl::texture &character() { return instance->s_character; }
        static const sdl::texture &role() { return instance->s_role; }
        static const sdl::texture &goldrush() { return instance->s_goldrush; }
        static const sdl::texture &card_border() { return instance->s_card_border; }
        static const sdl::texture &cube() { return instance->s_cube; }
        static const sdl::texture &cube_border() { return instance->s_cube_border; }
        static const sdl::texture &gold() { return instance->s_gold; }

        friend class game_scene;
    };

    struct card_view;

    class card_pile_view : public std::vector<card_view *> {
    protected:
        sdl::point pos;
        int m_width;
        int hflip;

    public:
        uint32_t border_color = 0;

        explicit card_pile_view(int width = 0, bool hflip = false)
            : m_width(width)
            , hflip(hflip ? -1 : 1) {}

        const sdl::point get_pos() const { return pos; }
        int width() const { return m_width; }

        void set_pos(const sdl::point &new_pos);
        virtual sdl::point get_position_of(card_view *card) const;
        void erase_card(card_view *card);
    };

    struct character_pile : card_pile_view {
        sdl::point get_position_of(card_view *card) const override;
    };

    class cube_widget {
    public:
        card_view *owner = nullptr;

        int id;
        sdl::point pos;

        bool animating = false;
        uint32_t border_color = 0;

        cube_widget(int id) : id(id) {}

        void render(sdl::renderer &renderer, bool skip_if_animating = true);
    };

    class card_view : public card_info {
    public:
        std::vector<cube_widget *> cubes;

        float flip_amt = 0.f;
        float rotation = 0.f;

        bool animating = false;
        
        bool known = false;
        card_pile_view *pile = nullptr;

        bool inactive = false;

        uint32_t border_color = 0;

        void set_pos(const sdl::point &pos);
        const sdl::point &get_pos() const {
            return m_pos;
        }

        const sdl::rect &get_rect() const {
            return m_rect;
        }

        void render(sdl::renderer &renderer, bool skip_if_animating = true);

        sdl::texture texture_front;
        sdl::texture texture_front_scaled;

        const sdl::texture *texture_back = nullptr;

        void set_texture_front(sdl::texture &&tex) {
            texture_front = std::move(tex);
            texture_front_scaled = sdl::scale_surface(texture_front.get_surface(),
                texture_front.get_rect().w / sizes::card_width);
        }
        
        void make_texture_front();

    private:
        sdl::point m_pos;
        sdl::rect m_rect;
    };

    struct role_card : card_view {
        player_role role = player_role::unknown;

        void make_texture_front();
    };
}

#endif