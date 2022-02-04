#ifndef __REQUESTS_ARMEDANDDANGEROUS_H__
#define __REQUESTS_ARMEDANDDANGEROUS_H__

#include "card_effect.h"

namespace banggame {

    struct request_add_cube : request_base {
        request_add_cube(card *origin_card, player *target, int ncubes = 1)
            : request_base(origin_card, nullptr, target)
            , ncubes(ncubes) {}

        int ncubes = 1;
        
        bool can_pick(card_pile_type pile, player *target, card *target_card) const;
        void on_pick(card_pile_type pile, player *target, card *target_card);
        game_formatted_string status_text() const;
    };

    struct request_move_bomb : request_base, allowed_piles<card_pile_type::player> {
        request_move_bomb(card *origin_card, player *target)
            : request_base(origin_card, nullptr, target) {}

        void on_pick(card_pile_type pile, player *target, card *target_card);
        game_formatted_string status_text() const;
    };

    struct request_rust : request_base {
        using request_base::request_base;

        void on_resolve();
        game_formatted_string status_text() const;
    };

    struct timer_al_preacher : timer_base {
        using timer_base::timer_base;
        game_formatted_string status_text() const;
    };

    struct timer_tumbleweed : timer_base {
        timer_tumbleweed(card *origin_card, player *target, card *drawn_card, card *drawing_card)
            : timer_base(origin_card, nullptr, target)
            , target_card(drawing_card)
            , drawn_card(drawn_card) {}
        
        card *target_card;
        card *drawn_card;

        void on_finished();
        game_formatted_string status_text() const;
    };
}

#endif