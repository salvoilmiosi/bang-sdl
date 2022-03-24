#ifndef __EFFECTS_BASE_H__
#define __EFFECTS_BASE_H__

#include "card_effect.h"

namespace banggame {

    struct effect_play_card_action {
        void on_play(card *origin_card, player *origin);
    };

    struct effect_max_usages {
        int max_usages;
        
        void verify(card *origin_card, player *origin) const;
        bool can_respond(card *origin_card, player *origin) const;
        void on_play(card *origin_card, player *origin);
    };

    struct effect_pass_turn {
        void verify(card *origin_card, player *origin) const;
        void on_play(card *origin_card, player *origin);
    };

    struct effect_resolve {
        bool can_respond(card *origin_card, player *origin) const;
        void on_play(card *origin_card, player *origin);
    };
    
    struct effect_bang {
        void on_play(card *origin_card, player *origin, player *target, effect_flags flags = {});
    };

    struct effect_bangcard {
        void on_play(card *origin_card, player *origin, player *target, effect_flags flags = {});
    };

    struct effect_banglimit {
        void verify(card *origin_card, player *origin) const;
        void on_play(card *origin_card, player *origin);
    };

    struct effect_indians {
        void on_play(card *origin_card, player *origin, player *target, effect_flags flags = {});
    };

    struct effect_duel {
        void on_play(card *origin_card, player *origin, player *target, effect_flags flags = {});
    };
    
    struct effect_missed {
        bool can_respond(card *origin_card, player *origin) const;
        void on_play(card *origin_card, player *origin);
    };

    struct effect_bangresponse {
        bool can_respond(card *origin_card, player *origin) const;
        void on_play(card *origin_card, player *origin);
    };
    
    struct effect_barrel : effect_missed {
        void on_play(card *origin_card, player *target);
    };

    struct effect_beer {
        void on_play(card *origin_card, player *origin) {
            on_play(origin_card, origin, origin);
        }
        void on_play(card *origin_card, player *origin, player *target);
    };

    struct effect_heal {
        int amount;
        effect_heal(int value) : amount(std::max(1, value)) {}

        void on_play(card *origin_card, player *origin) {
            on_play(origin_card, origin, origin);
        }
        void on_play(card *origin_card, player *origin, player *target);
    };

    struct effect_heal_notfull : effect_heal {
        void verify(card *origin_card, player *origin, player *target) const;
    };

    struct effect_deathsave {
        bool can_respond(card *origin_card, player *origin) const;
        void on_play(card *origin_card, player *origin);
    };

    struct effect_destroy {
        void on_play(card *origin_card, player *origin, player *target, card *target_card, effect_flags flags = {});
        void on_resolve(card *origin_card, player *origin, player *target, card *target_card);
    };

    struct effect_choose_card {
        void on_play(card *origin_card, player *origin, player *target, card *target_card);
    };

    struct effect_draw {
        int ncards;
        effect_draw(int value) : ncards(std::max(1, value)) {}
        
        void on_play(card *origin_card, player *origin) {
            on_play(origin_card, origin, origin);
        }
        void on_play(card *origin_card, player *origin, player *target);
    };

    struct effect_draw_discard {
        void verify(card *origin_card, player *origin, player *target) const;
        void on_play(card *origin_card, player *origin, player *target);
    };

    struct effect_draw_to_discard {
        int ncards;
        effect_draw_to_discard(int value) : ncards(std::max(1, value)) {}

        void on_play(card *origin_card, player *origin);
    };

    struct effect_drawing {
        bool ends_drawing = false;
        effect_drawing(int value) : ends_drawing(value != 0) {}

        bool can_respond(card *origin_card, player *origin) const;
        void on_play(card *origin_card, player *origin);
    };

    struct effect_draw_one_less {
        void on_play(card *origin_card, player *target);
    };

    struct effect_steal {
        void on_play(card *origin_card, player *origin, player *target, card *target_card, effect_flags flags = {});
        void on_resolve(card *origin_card, player *origin, player *target, card *target_card);
    };

    struct effect_generalstore {
        void on_play(card *origin_card, player *origin);
    };

    struct effect_damage {
        void verify(card *origin_card, player *origin, player *target) const;
        void on_play(card *origin_card, player *origin, player *target);
    };

}

#endif