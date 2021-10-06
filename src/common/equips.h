#ifndef __EQUIPS_H__
#define __EQUIPS_H__

#include "effects.h"

namespace banggame {

    struct event_based_effect : card_effect {
        void on_unequip(player *target, int card_id);
    };

    struct effect_mustang : card_effect {
        void on_equip(player *target, int card_id);
        void on_unequip(player *target, int card_id);
    };

    struct effect_scope : card_effect {
        void on_equip(player *target, int card_id);
        void on_unequip(player *target, int card_id);
    };

    struct effect_jail : card_effect {
        void on_equip(player *target, int card_id);
        void on_unequip(player *target, int card_id);
        void on_predraw_check(player *target, int card_id);
    };

    struct effect_dynamite : card_effect {
        void on_equip(player *target, int card_id);
        void on_unequip(player *target, int card_id);
        void on_predraw_check(player *target, int card_id);
    };

    struct effect_snake : card_effect {
        void on_equip(player *target, int card_id);
        void on_unequip(player *target, int card_id);
        void on_predraw_check(player *target, int card_id);
    };

    struct effect_weapon : card_effect {
        void on_equip(player *target, int card_id);
        void on_unequip(player *target, int card_id);
    };

    struct effect_volcanic : card_effect {
        void on_equip(player *target, int card_id);
        void on_unequip(player *target, int card_id);
    };

    struct effect_boots : event_based_effect {
        void on_equip(player *target, int card_id);
    };

    struct effect_horsecharm : card_effect {
        void on_equip(player *target, int card_id);
        void on_unequip(player *target, int card_id);
    };

    struct effect_pickaxe : card_effect {
        void on_equip(player *target, int card_id);
        void on_unequip(player *target, int card_id);
    };

    struct effect_calumet : card_effect {
        void on_equip(player *target, int card_id);
        void on_unequip(player *target, int card_id);
    };

    struct effect_ghost : event_based_effect {
        void on_equip(player *target, int card_id);
    };

    struct effect_shotgun : event_based_effect {
        void on_equip(player *target, int card_id);
    };

    struct effect_bounty : event_based_effect {
        void on_equip(player *target, int card_id);
    };

    struct effect_bandidos : card_effect {
        void on_play(player *origin, player *target);
    };

    struct effect_tornado : card_effect {
        void on_play(player *origin, player *target);
    };

    struct effect_poker : card_effect {
        void on_play(player *origin);
    };

}

#endif