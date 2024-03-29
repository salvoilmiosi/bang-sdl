#include "cards/filters.h"

#include "player.h"
#include "game.h"

namespace banggame::filters::detail {

    bool check_player_flags(const player_view *origin, player_flags flags) {
        return origin->has_player_flags(flags);
    }

    bool check_game_flags(const player_view *origin, game_flags flags) {
        return origin->m_game->has_game_flags(flags);
    }

    player_role get_player_role(player_view *origin) {
        return origin->m_role.role;
    }

    int get_player_range_mod(const player_view *origin) {
        return origin->m_game->get_target_finder().get_request_status().m_distances.range_mod;
    }

    int get_player_weapon_range(const player_view *origin) {
        return origin->m_game->get_target_finder().get_request_status().m_distances.weapon_range;
    }

    int count_player_hand_cards(player_view *origin) {
        return int(origin->hand.size());
    }

    int count_player_table_cards(player_view *origin) {
        return int(rn::count_if(origin->table, std::not_fn(&card_view::is_black)));
    }

    int count_player_cubes(player_view *origin) {
        return rn::accumulate(
            rv::concat(origin->table, origin->m_characters)
            | rv::transform([](card_view *card) { return card->cubes.size(); }),
            0
        );
    }

    int get_distance(player_view *origin, player_view *target) {
        return origin->m_game->get_target_finder().calc_distance(origin, target);
    }

    const player_view *get_card_owner(card_view *target) {
        if (target->pocket) {
            return target->pocket->owner;
        }
        return nullptr;
    }

    card_sign get_card_sign(card_view *target) {
        return target->sign;
    }

    card_color_type get_card_color(card_view *target) {
        return target->color;
    }

    pocket_type get_card_pocket(card_view *target) {
        return target->pocket->type;
    }

    card_deck_type get_card_deck(card_view *target) {
        return target->deck;
    }

    bool is_cube_slot(card_view *target) {
        return target == target->pocket->owner->m_characters.front()
            || target->is_orange() && target->pocket->type == pocket_type::player_table;
    }

    std::optional<short> get_card_tag(card_view *target, tag_type type) {
        return target->get_tag_value(type);
    }

    card_view *get_request_origin_card(player_view *origin) {
        return origin->m_game->get_target_finder().get_request_status().m_request_origin_card;
    }

    player_view *get_request_origin(player_view *origin) {
        return origin->m_game->get_target_finder().get_request_status().m_request_origin;
    }

    target_list get_request_target_set(player_view *origin) {
        return origin->m_game->get_target_finder().get_request_status().m_request_target_set;
    }

    bool can_pick_card(player_view *origin, card_view *target) {
        return rn::contains(origin->m_game->get_target_finder().get_request_status().m_pick_cards, target);
    }
}