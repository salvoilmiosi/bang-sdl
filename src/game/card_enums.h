#ifndef __CARD_ENUMS_H__
#define __CARD_ENUMS_H__

#include "utils/enum_variant.h"

namespace banggame {

    struct card_suit_symbol {
        std::string_view letter;
        std::string_view symbol;
    };

    DEFINE_ENUM_DATA_IN_NS(banggame, card_suit_type,
        (none,      card_suit_symbol{"-", "-"})
        (hearts,    card_suit_symbol{"C", "\u2665"})
        (diamonds,  card_suit_symbol{"Q", "\u2666"})
        (clubs,     card_suit_symbol{"F", "\u2663"})
        (spades,    card_suit_symbol{"P", "\u2660"})
    )

    DEFINE_ENUM_DATA_IN_NS(banggame, card_value_type,
        (none,      "-")
        (value_A,   "A")
        (value_2,   "2")
        (value_3,   "3")
        (value_4,   "4")
        (value_5,   "5")
        (value_6,   "6")
        (value_7,   "7")
        (value_8,   "8")
        (value_9,   "9")
        (value_10,  "10")
        (value_J,   "J")
        (value_Q,   "Q")
        (value_K,   "K")
    )
    
    DEFINE_ENUM_FLAGS_IN_NS(banggame, card_expansion_type,
        (base)
        (characterchoice)
        (dodgecity)
        (goldrush)
        (armedanddangerous)
        (valleyofshadows)
        (canyondiablo)
        (highnoon)
        (fistfulofcards)
        (wildwestshow)
        (thebullet)
        (ghostcards)
    )

    DEFINE_ENUM_IN_NS(banggame, card_color_type,
        (none)
        (brown)
        (blue)
        (green)
        (black)
        (orange)
    )

    DEFINE_ENUM_IN_NS(banggame, player_role,
        (unknown)
        (sheriff)
        (deputy)
        (outlaw)
        (renegade)
    )

    DEFINE_ENUM_FLAGS_IN_NS(banggame, target_player_filter,
        (dead)
        (self)
        (notself)
        (notsheriff)
        (range_1)
        (range_2)
        (reachable)
    )

    DEFINE_ENUM_FLAGS_IN_NS(banggame, target_card_filter,
        (table)
        (hand)
        (blue)
        (black)
        (clubs)
        (bang)
        (missed)
        (beer)
        (bronco)
        (cube_slot)
        (cube_slot_card)
        (can_repeat)
    )

    DEFINE_ENUM_TYPES_IN_NS(banggame, play_card_target_type,
        (none)
        (player, int)
        (card, int)
        (other_players)
        (cards_other_players, std::vector<int>)
    )

    using play_card_target = enums::enum_variant<play_card_target_type>;

    DEFINE_ENUM_IN_NS(banggame, card_deck_type,
        (none)
        (main_deck)
        (character)
        (role)
        (goldrush)
        (highnoon)
        (fistfulofcards)
        (wildwestshow)
    )

    DEFINE_ENUM_IN_NS(banggame, card_pile_type,
        (none)
        (player)
        (player_hand)
        (player_table)
        (player_character)
        (player_backup)
        (main_deck)
        (discard_pile)
        (selection)
        (shop_deck)
        (shop_discard)
        (shop_selection)
        (hidden_deck)
        (scenario_deck)
        (scenario_card)
        (specials)
    )

    DEFINE_ENUM_IN_NS(banggame, card_modifier_type,
        (none)
        (bangcard)
        (discount)
        (leevankliff)
        (shopchoice)
    )

    DEFINE_ENUM_FLAGS_IN_NS(banggame, effect_flags,
        (escapable)
        (single_target)
    )

}

#endif