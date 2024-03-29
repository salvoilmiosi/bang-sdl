#include "animations.h"

namespace banggame {

    using namespace sdl::point_math;

    float ease_in_out_pow(float exp, float x) {
        return x < 0.5f ? std::pow(2.f * x, exp) / 2.f : 1.f - std::pow(-2.f * x + 2.f, exp) / 2.f;
    }

    constexpr sdl::point lerp_point(sdl::point begin, sdl::point end, float amt) {
        return {
            int(std::lerp(float(begin.x), float(end.x), amt)),
            int(std::lerp(float(begin.y), float(end.y), amt))
        };
    }

    void player_move_animation::add_move_player(player_view *player, sdl::point end) {
        data.emplace_back(player, player->get_position(), end);
    }

    void player_move_animation::end() {
        for (auto &p : data) {
            p.player->set_position(p.end);
        }
    }

    void player_move_animation::do_animation_impl(float amt) {
        for (auto &p : data) {
            p.player->set_position(lerp_point(p.begin, p.end, amt));
        }
    }

    void card_move_animation::add_move_card(card_view *card) {
        if (rn::find(data, card, &decltype(data)::value_type::first) == data.end()) {
            data.emplace_back(card, card->get_pos());
        }
    }

    void card_move_animation::end() {
        for (auto &[card, _] : data) {
            card->set_pos(card->pocket->get_pos() + card->pocket->get_offset(card));
            card->animating = false;
        }
    }

    void card_move_animation::do_animation_impl(float amt) {
        for (auto &[card, start] : data) {
            card->set_pos(lerp_point(start, card->pocket->get_pos() + card->pocket->get_offset(card), amt));
            card->animating = true;
        }
    }

    void card_move_animation::render(sdl::renderer &renderer) {
        for (auto &[card, _] : data) {
            card->render(renderer, render_flags::no_skip_animating);
        }
    }

    void card_flip_animation::end() {
        if (flips) {
            card->texture_front.reset();
            card->texture_front_scaled.reset();
            card->flip_amt = 0.f;
        } else {
            card->flip_amt = 1.f;
        }
        card->animating = false;
    }

    void card_flip_animation::do_animation_impl(float amt) {
        card->animating = true;
        card->flip_amt = flips ? 1.f - amt : amt;
    }

    void card_flip_animation::render(sdl::renderer &renderer) {
        card->render(renderer, render_flags::no_skip_animating);
    }

    void deck_shuffle_animation::end() {
        for (card_view *card : *cards) {
            card->animating = false;
            card->flip_amt = 0.f;
            card->set_pos(cards->get_pos());
        }
    }

    void deck_shuffle_animation::do_animation(float x) {
        const float off = options.shuffle_deck_offset;
        const float diff = off / cards->size();
        const float m = 1.f / (1.f - off);
        
        float n = off;
        for (card_view *card : *cards) {
            const float amt = ease_in_out_pow(options.easing_exponent, std::clamp(m * (x - n), 0.f, 1.f));
            card->animating = true;
            card->flip_amt = 1.f - amt;
            card->set_pos(lerp_point(start_pos, cards->get_pos(), amt));
            n -= diff;
        }
    }

    void deck_shuffle_animation::render(sdl::renderer &renderer) {
        auto first_card = rn::find_if(*cards, [](card_view *card) { return card->flip_amt <= 0.5f; });
        for (card_view *card : rn::subrange(first_card, cards->end()) | rv::reverse) {
            card->render(renderer, render_flags::no_skip_animating);
        }
        for (card_view *card : rn::subrange(cards->begin(), first_card)) {
            card->render(renderer, render_flags::no_skip_animating);
        }
    }

    void card_tap_animation::end() {
        card->animating = false;
        card->rotation = taps ? 90.f : 0.f;
    }

    void card_tap_animation::do_animation_impl(float amt) {
        card->animating = true;
        card->rotation = 90.f * (taps ? amt : 1.f - amt);
    }

    void card_tap_animation::render(sdl::renderer &renderer) {
        card->render(renderer, render_flags::no_skip_animating);
    }

    card_flash_animation::card_flash_animation(card_view *card)
        : card(card) {}

    void card_flash_animation::end() {
        card->animating = false;
        card->flash_amt = 0.f;
    }

    void card_flash_animation::do_animation(float amt) {
        card->animating = true;
        card->flash_amt = std::pow(1.f - amt, options.flash_exponent);
    }

    void card_flash_animation::render(sdl::renderer &renderer) {
        card->render(renderer, render_flags::no_skip_animating);
    }

    void player_hp_animation::do_animation_impl(float amt) {
        player->set_hp_marker_position(std::lerp(float(hp_from), float(hp_to), amt));
    }

    void cube_move_animation::render(sdl::renderer &renderer) {
        for (auto &item : data) {
            item.cube->render(renderer, render_flags::no_skip_animating);
        }
    }

    void cube_move_animation::do_animation(float x) {
        const float off = options.move_cubes_offset;
        const float diff = off / data.size();
        const float m = 1.f / (1.f - off);
        
        float n = off;
        for (auto &item : data) {
            const float amt = ease_in_out_pow(options.easing_exponent, data.size() == 1 ? x : std::clamp(m * (x - n), 0.f, 1.f));

            item.cube->pos = lerp_point(item.start, item.pile->get_pos() + item.offset, amt);
            item.cube->animating = true;
            n -= diff;
        }
    }

    void cube_move_animation::end() {
        for (auto &item : data) {
            item.cube->pos = item.pile->get_pos() + item.offset;
            item.cube->animating = false;
        }
    }

    sdl::point train_move_animation::end_point() const {
        return stations->get_pos() + options.train_offset + options.train_card_offset * end_pos;
    }

    void train_move_animation::end() {
        train->set_pos(end_point());
    }

    void train_move_animation::do_animation_impl(float amt) {
        train->set_pos(lerp_point(start_pos, end_point(), amt));
    }

    void pause_animation::render(sdl::renderer &renderer) {
        if (card) {
            card->render(renderer, render_flags::no_skip_animating);
        }
    }

    void pause_animation::do_animation(float) {
        if (card) {
            card->animating = true;
        }
    }

    void pause_animation::end() {
        if (card) {
            card->animating = false;
        }
    }

}