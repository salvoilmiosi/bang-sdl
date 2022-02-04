#ifndef __EQUIPS_ARMEDANDDANGEROUS_H__
#define __EQUIPS_ARMEDANDDANGEROUS_H__

#include "card_effect.h"

namespace banggame {
    
    struct effect_bomb : card_effect {
        void on_equip(card *target_card, player *target);
        void on_unequip(card *target_card, player *target);
    };

    struct effect_tumbleweed : event_based_effect {
        void on_equip(card *target_card, player *target);

        bool can_respond(card *origin_card, player *origin) const;
        void on_play(card *origin_card, player *target);
    };
}

#endif