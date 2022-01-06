#ifndef __GAME_UPDATE_H__
#define __GAME_UPDATE_H__

#include "card_enums.h"
#include "requests.h"
#include "timer.h"

namespace banggame {

    struct game_over_update {REFLECTABLE(
        (player_role) winner_role
    )};

    struct add_cards_update {REFLECTABLE(
        (std::vector<int>) card_ids,
        (card_pile_type) pile
    )};

    DEFINE_ENUM_FLAGS_IN_NS(banggame, show_card_flags,
        (short_pause)
        (no_animation)
        (show_everyone)
    )

    struct move_card_update {REFLECTABLE(
        (int) card_id,
        (int) player_id,
        (card_pile_type) pile,
        (show_card_flags) flags
    )};

    struct add_cubes_update {REFLECTABLE(
        (std::vector<int>) cubes
    )};

    struct move_cube_update {REFLECTABLE(
        (int) cube_id,
        (int) card_id
    )};

    struct card_target_data {REFLECTABLE(
        (effect_type) type,
        (target_type) target,
        (int) args
    )};

    struct equip_target_data {REFLECTABLE(
        (equip_type) type,
        (target_type) target,
        (int) args
    )};

    struct card_info {REFLECTABLE(
        (int) id,
        (card_expansion_type) expansion,
        (std::string) name,
        (std::string) image,
        (std::vector<card_target_data>) targets,
        (std::vector<card_target_data>) response_targets,
        (std::vector<card_target_data>) optional_targets,
        (std::vector<equip_target_data>) equip_targets,
        (card_modifier_type) modifier
    )};

    struct show_card_update {REFLECTABLE(
        (card_info) info,
        (card_suit_type) suit,
        (card_value_type) value,
        (card_color_type) color,
        (show_card_flags) flags
    )};

    struct player_character_update {REFLECTABLE(
        (card_info) info,
        (int) max_hp,
        (int) player_id,
        (int) index
    )};

    struct player_remove_character_update {REFLECTABLE(
        (int) player_id,
        (int) card_id
    )};

    struct hide_card_update {REFLECTABLE(
        (int) card_id,
        (show_card_flags) flags,
        (int) ignore_player_id
    )};

    struct tap_card_update {REFLECTABLE(
        (int) card_id,
        (bool) inactive,
        (bool) instant
    )};

    struct last_played_card_id {REFLECTABLE(
        (int) card_id
    )};

    struct player_user_update {REFLECTABLE(
        (int) player_id,
        (int) user_id
    )};

    struct player_hp_update {REFLECTABLE(
        (int) player_id,
        (int) hp,
        (bool) dead,
        (bool) instant
    )};

    struct player_gold_update {REFLECTABLE(
        (int) player_id,
        (int) gold
    )};

    struct player_show_role_update {REFLECTABLE(
        (int) player_id,
        (player_role) role,
        (bool) instant
    )};

    DEFINE_ENUM_FLAGS_IN_NS(banggame, player_flags,
        (dead)
        (ghost)
        (has_drawn)
        (start_of_turn)
        (see_everyone_range_1)
        (treat_missed_as_bang)
        (treat_any_as_bang)
    )

    struct player_status_update {REFLECTABLE(
        (int) player_id,
        (player_flags) flags,
        (int) range_mod,
        (int) weapon_range,
        (int) distance_mod
    )};

    struct switch_turn_update {REFLECTABLE(
        (int) player_id
    )};

    struct request_status_args {REFLECTABLE(
        (request_type) type,
        (int) origin_id,
        (int) target_id,
        (effect_flags) flags,
        (game_formatted_string) status_text
    )};

    DEFINE_ENUM_TYPES_IN_NS(banggame, game_update_type,
        (game_over, game_over_update)
        (game_error, game_formatted_string)
        (game_log, game_formatted_string)
        (add_cards, add_cards_update)
        (move_card, move_card_update)
        (add_cubes, add_cubes_update)
        (move_cube, move_cube_update)
        (deck_shuffled, card_pile_type)
        (show_card, show_card_update)
        (hide_card, hide_card_update)
        (tap_card, tap_card_update)
        (last_played_card, last_played_card_id)
        (player_add, player_user_update)
        (player_hp, player_hp_update)
        (player_gold, player_gold_update)
        (player_add_character, player_character_update)
        (player_remove_character, player_remove_character_update)
        (player_show_role, player_show_role_update)
        (player_status, player_status_update)
        (switch_turn, switch_turn_update)
        (request_status, request_status_args)
        (status_clear)
    )

    using game_update = enums::enum_variant<game_update_type>;
}

#endif