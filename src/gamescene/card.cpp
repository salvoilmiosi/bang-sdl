#include "card.h"

#include "net/options.h"
#include "../media_pak.h"

#include <fmt/format.h>

namespace banggame {

    using namespace sdl::point_math;

    template<typename T>
    concept first_is_none = requires {
        requires enums::reflected_enum<T>;
        T::none;
        requires int(T::none) == 0;
    };

    template<typename ESeq> struct remove_first{};

    template<first_is_none auto None, first_is_none auto ... Es>
    struct remove_first<enums::enum_sequence<None, Es ...>> : enums::enum_sequence<Es ...> {};

    template<first_is_none T>
    struct skip_none : remove_first<enums::make_enum_sequence<T>> {};

    card_textures::card_textures(const std::filesystem::path &base_path, sdl::renderer &renderer)
        : cards_pak_data(ifstream_or_throw(base_path / "cards.pak"))
        , card_resources(cards_pak_data)

        , card_mask (get_card_resource("misc/card_mask"))
        , card_border (renderer, get_card_resource("misc/card_border"))

        , rank_icons([&]<card_rank ... Es>(enums::enum_sequence<Es ...>) {
            return std::array {
                get_card_resource(fmt::format("misc/{}", enums::to_string(Es))) ...
            };
        }(skip_none<card_rank>()))

        , suit_icons([&]<card_suit ... Es>(enums::enum_sequence<Es ...>) {
            return std::array {
                get_card_resource(fmt::format("misc/suit_{}", enums::to_string(Es))) ...
            };
        }(skip_none<card_suit>()))
    {
        s_instance = this;
    }

    sdl::texture_ref card_textures::get_backface_texture(std::string_view name, sdl::renderer &renderer) const {
        if (auto it = backfaces.find(name); it != backfaces.end()) {
            return it->second;
        } else if (card_resources.contains(name)) {
            return backfaces.emplace(std::piecewise_construct,
                std::forward_as_tuple(name),
                std::forward_as_tuple(renderer, apply_card_mask(get_card_resource(name)))
            ).first->second;
        } else {
            return {};
        }
    }
    
    sdl::surface card_textures::apply_card_mask(const sdl::surface &source) const {
        sdl::surface ret(card_mask.get()->w, card_mask.get()->h);
        sdl::rect src_rect = source.get_rect();
        sdl::rect dst_rect = ret.get_rect();
        SDL_BlitSurface(source.get(), &src_rect, ret.get(), &dst_rect);

        SDL_LockSurface(card_mask.get());
        SDL_LockSurface(ret.get());

        const uint32_t amask = card_mask.get()->format->Amask;

        uint32_t *mask_ptr = static_cast<uint32_t *>(card_mask.get()->pixels);
        uint32_t *surf_ptr = static_cast<uint32_t *>(ret.get()->pixels);

        int npixels = ret.get()->w * ret.get()->h;

        for (int i=0; i<npixels; ++i) {
            *surf_ptr = (*surf_ptr & (~amask)) | (*mask_ptr & amask);
            ++mask_ptr;
            ++surf_ptr;
        }

        SDL_UnlockSurface(ret.get());
        SDL_UnlockSurface(card_mask.get());

        return ret;
    }

    static std::string parse_image(std::string_view image, card_deck_type deck, bool backface = false) {
        auto colon_index = image.find(':');
        if (backface) {
            if (colon_index != std::string_view::npos) {
                image = image.substr(colon_index + 1);
            } else {
                return fmt::format("backface/{}", enums::to_string(deck));
            }
        } else if (colon_index != std::string_view::npos) {
            image = image.substr(0, colon_index);
        }
        if (rn::contains(image, '/')) {
            return std::string(image);
        } else {
            return fmt::format("{}/{}", enums::to_string(deck), image);
        }
    }

    void card_view::make_texture_front(sdl::renderer &renderer) {
        auto do_make_texture = [&](float scale) {
            sdl::surface card_base_surf;
            try {
                card_base_surf = card_textures::get().get_card_resource(parse_image(image, deck));
            } catch (const std::out_of_range &error) {
                fmt::print("{}\n", error.what());
                sdl::rect mask_rect = card_textures::get().card_mask.get_rect();
                card_base_surf = sdl::surface{mask_rect.w, mask_rect.h};
                uint32_t color = SDL_MapRGBA(card_base_surf.get()->format, 0xff, 0x0, 0xff, 0xff);
                SDL_FillRect(card_base_surf.get(), nullptr, color);
            }

            if (sign) {
                sdl::rect card_rect = card_base_surf.get_rect();

                const auto &card_rank_surf = card_textures::get().rank_icons[enums::indexof(sign.rank) - 1];
                sdl::rect rank_rect = card_rank_surf.get_rect();

                rank_rect.w = int(rank_rect.w * scale);
                rank_rect.h = int(rank_rect.h * scale);
                rank_rect.x = options.card_suit_offset;
                rank_rect.y = card_rect.h - rank_rect.h - options.card_suit_offset;
                    
                SDL_BlitScaled(card_rank_surf.get(), nullptr, card_base_surf.get(), &rank_rect);
                
                const auto &card_suit_surf = card_textures::get().suit_icons[enums::indexof(sign.suit) - 1];
                sdl::rect suit_rect = card_suit_surf.get_rect();

                suit_rect.w = int(suit_rect.w * scale);
                suit_rect.h = int(suit_rect.h * scale);
                suit_rect.x = rank_rect.x + rank_rect.w;
                suit_rect.y = card_rect.h - suit_rect.h - options.card_suit_offset;

                SDL_BlitScaled(card_suit_surf.get(), nullptr, card_base_surf.get(), &suit_rect);
            }

            return card_base_surf;
        };

        sdl::surface surface_front = card_textures::get().apply_card_mask(do_make_texture(1.f));
        texture_front = sdl::texture(renderer, surface_front);

        sdl::surface scaled = card_textures::get().apply_card_mask(do_make_texture(options.card_suit_scale));
        sdl::surface surface_front_scaled = sdl::scale_surface(scaled, scaled.get_rect().w / options.card_width);
        texture_front_scaled = sdl::texture(renderer, surface_front_scaled);
    }

    void card_view::make_texture_back(sdl::renderer &renderer) {
        texture_back = card_textures::get().get_backface_texture(parse_image(image, deck, true), renderer);
    }

    void role_card::make_texture_front(sdl::renderer &renderer) {
        sdl::surface surface_front = card_textures::get().apply_card_mask(
            card_textures::get().get_card_resource(fmt::format("role/{}", enums::to_string(role))));
        texture_front = sdl::texture(renderer, surface_front);
        texture_front_scaled = sdl::texture(renderer, sdl::scale_surface(surface_front,
            texture_front.get_rect().w / options.card_width));
    }

    void role_card::make_texture_back(sdl::renderer &renderer) {
        texture_back = card_textures::get().get_backface_texture(parse_image("", card_deck_type::role, true), renderer);
    }

    void cube_widget::render(sdl::renderer &renderer, render_flags flags) {
        auto do_render = [&](sdl::texture_ref tex, sdl::color color = sdl::rgb(0xffffff)) {
            tex.render_colored(renderer, sdl::move_rect_center(tex.get_rect(), pos), color);
        };

        if (bool(flags & render_flags::no_skip_animating) || !animating) {
            if (auto style = get_style()) {
                do_render(media_pak::get().sprite_cube_border, cube_border_color(*style));
            }
            do_render(media_pak::get().sprite_cube);
        }
    }

    void card_view::set_pos(const sdl::point &new_pos) {
        cubes.set_pos(new_pos);
        m_pos = new_pos;
    }

    sdl::rect card_view::get_base_rect(sdl::texture_ref tex) const {
        sdl::rect rect = tex.get_rect();
        sdl::scale_rect_width(rect, options.card_width);
        return sdl::move_rect_center(rect, m_pos);
    }

    sdl::rect card_view::get_rect() const {
        if (sdl::texture_ref tex = get_texture()) {
            sdl::rect rect = get_base_rect(tex);
            if (inactive) {
                return sdl::move_rect_center(sdl::rect{0, 0, rect.h, rect.w}, sdl::rect_center(rect));
            } else {
                return rect;
            }
        }
        return sdl::rect{};
    }

    sdl::texture_ref card_view::get_texture() const {
        if (flip_amt > 0.5f && texture_front_scaled) {
            return texture_front_scaled;
        } else if (texture_back) {
            return texture_back;
        } else {
            return nullptr;
        }
    }

    void card_view::render(sdl::renderer &renderer, render_flags flags) {
        sdl::texture_ref tex = get_texture();
        if (!tex || animating && !bool(flags & render_flags::no_skip_animating)) return;

        sdl::rect rect = get_base_rect(tex);
        float wscale = std::abs(1.f - 2.f * flip_amt);
        rect.x += int(rect.w * (1.f - wscale) * 0.5f);
        rect.w = int(rect.w * wscale);

        if (!bool(flags & render_flags::no_draw_border)) {
            sdl::color border_color{};
            if (auto style = get_style()) {
                border_color = card_border_color(*style);
            }
            border_color = sdl::lerp_color(border_color, colors.flash_card, flash_amt);
            if (border_color.a) {
                card_textures::get().card_border.render_ex(renderer, sdl::rect{
                    rect.x - options.default_border_thickness,
                    rect.y - options.default_border_thickness,
                    rect.w + options.default_border_thickness * 2,
                    rect.h + options.default_border_thickness * 2
                }, sdl::render_ex_options{
                    .color_modifier = border_color,
                    .angle = rotation
                });
            }
        }

        tex.render_ex(renderer, rect, sdl::render_ex_options{ .angle = rotation });

        for (auto &cube : cubes) {
            cube->render(renderer);
        }
    }

    void pocket_view_base::add_card(card_view *card) {
        m_cards.push_back(card);
    }

    void pocket_view_base::erase_card(card_view *card) {
        if (auto it = rn::find(*this, card); it != end()) {
            m_cards.erase(it);
        }
    }

    void pocket_view_base::clear() {
        m_cards.clear();
    }

    card_view *pocket_view_base::find_card_at(sdl::point point) const {
        auto range = *this | rv::reverse;
        auto it = rn::find_if(range, [&](card_view *card) {
            return sdl::point_in_rect(point, card->get_rect());
        });
        return (it == range.end()) ? nullptr : *it;
    }

    void pocket_view_base::render(sdl::renderer &renderer) {
        for (card_view *c : *this) {
            c->render(renderer);
        }
    }

    void pocket_view_base::render_first(sdl::renderer &renderer, int ncards) {
        for (card_view *c : *this | rv::take(ncards)) {
            c->render(renderer);
        }
    }
    
    void pocket_view_base::render_last(sdl::renderer &renderer, int ncards) {
        if (!empty()) {
            for (card_view *c : *this
                | rv::take_last(ncards)
                | rv::drop_last(1)
            ) {
                c->render(renderer, render_flags::no_draw_border);
            }
            back()->render(renderer);
        }
    }

    void pocket_view_base::set_pos(const sdl::point &pos) {
        for (card_view *c : *this) {
            c->set_pos(c->get_pos() - m_pos + pos);
        }
        m_pos = pos;
    }

    card_view *point_pocket_view::find_card_at(sdl::point point) const {
        if (!empty() && sdl::point_in_rect(point, back()->get_rect())) {
            return back();
        }
        return nullptr;
    }

    void pocket_view::add_card(card_view *card) {
        card->pocket = this;
        pocket_view_base::add_card(card);
    }

    void pocket_view::erase_card(card_view *card) {
        card->pocket = nullptr;
        pocket_view_base::erase_card(card);
    }

    void pocket_view::clear() {
        for (card_view *card : *this) {
            if (card->pocket == this) {
                card->pocket = nullptr;
            }
        }
        pocket_view_base::clear();
    }

    sdl::point card_choice_pocket::get_offset(card_view *card) const {
        const float xoffset = float(options.card_width + options.card_choice_xoffset);
        const int diff = int(rn::distance(begin(), rn::find(*this, card)));
        return sdl::point{(int)(xoffset * (diff - (size() - 1) * .5f)), options.card_choice_yoffset};
    }

    void card_choice_pocket::set_anchor(card_view *card, const card_modifier_tree &tree) {
        anchor = card;
        set_pos(card->get_pos());
        for (const card_modifier_node &node : tree) {
            add_card(node.card);
        }
        for (card_view *c : *this) {
            c->set_pos(get_pos() + get_offset(c));
        }
    }

    void card_choice_pocket::clear() {
        pocket_view_base::clear();
        anchor = nullptr;
    }

    sdl::point wide_pocket::get_offset(card_view *card) const {
        if (size() == 1) {
            return {0, 0};
        }
        const float xoffset = std::min(float(width) / (size() - 1), float(options.card_width + options.card_pocket_xoff));
        const int diff = int(rn::distance(begin(), rn::find(*this, card)));
        return sdl::point{(int)(xoffset * (diff - (size() - 1) * .5f)), 0};
    }

    sdl::point flipped_pocket::get_offset(card_view *card) const {
        auto pt = wide_pocket::get_offset(card);
        return {- pt.x, pt.y};
    }

    sdl::point train_pocket::get_offset(card_view *card) const {
        const sdl::point diff = options.train_card_offset * int(rn::distance(begin(), rn::find(*this, card)));
        if (type == pocket_type::train) {
            return -diff;
        } else {
            return diff;
        }
    }

    sdl::point character_pile::get_offset(card_view *card) const {
        int diff = int(rn::distance(begin(), rn::find(*this, card)));
        return options.card_diag_offset * diff;
    }

    void counting_pocket::update_count() {
        m_count_text.set_value(std::to_string(size()));
    }

    void counting_pocket::render_count(sdl::renderer &renderer) {
        if (empty()) return;
        
        m_count_text.set_rect(sdl::move_rect_center(m_count_text.get_rect(), get_pos()));
        m_count_text.render(renderer);
    }

    sdl::point card_cube_pile::get_pos() const {
        return owner->get_pos();
    }

    sdl::point card_cube_pile::get_offset(cube_widget *cube) const {
        int diff = int(rn::distance(begin(), rn::find(*this, cube, &std::unique_ptr<cube_widget>::get)));
        return sdl::point{options.cube_xdiff, options.cube_ydiff + options.cube_yoff * diff};
    }

    void cube_pile_base::set_pos(sdl::point new_pos) {
        for (auto &cube : *this) {
            cube->pos = cube->pos + new_pos - get_pos();
        }
    }

    void table_cube_pile::set_pos(sdl::point pos) {
        cube_pile_base::set_pos(pos);
        m_pos = pos;
    }

    sdl::point table_cube_pile::get_offset(cube_widget *cube) const {
        auto rand_diff = []() {
            return int((float(std::rand()) / RAND_MAX - 0.5f) * options.cube_pile_size);
        };
        return sdl::point{rand_diff(), rand_diff()};
    }
}