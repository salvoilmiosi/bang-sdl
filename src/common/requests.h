#ifndef __REQUESTS_H__
#define __REQUESTS_H__

#include "effect_holder.h"
#include "characters.h"
#include "timer.h"

namespace banggame {

    struct request_predraw : picking_request_allowing<card_pile_type::player_table> {
        void on_pick(const pick_card_args &args);
    };

    struct request_check : picking_request_allowing<card_pile_type::selection> {
        bool invert_pop_req = false;
        
        void on_pick(const pick_card_args &args);
    };

    struct request_generalstore : picking_request_allowing<card_pile_type::selection> {
        void on_pick(const pick_card_args &args);
    };

    struct request_discard : picking_request_allowing<card_pile_type::player_hand> {
        void on_pick(const pick_card_args &args);
    };

    struct request_discard_pass : picking_request_allowing<card_pile_type::player_hand> {
        void on_pick(const pick_card_args &args);
    };

    struct request_damaging : request_base {
        void on_resolve();
    };

    struct request_bang : request_base {
        std::vector<int> barrels_used;
        int bang_strength = 1;
        int bang_damage = 1;
        bool unavoidable = false;
        bool is_bang_card = false;

        std::function<void()> cleanup_function;

        void on_resolve();
        void cleanup();
    };

    struct request_destroy : request_base {
        int card_id;

        void on_resolve();
    };

    struct request_steal : request_base {
        int card_id;

        void on_resolve();
    };

    struct request_death : request_base {
        std::vector<int> draw_attempts;
        
        void on_resolve();
    };

    struct request_bandidos : picking_request_allowing<card_pile_type::player_hand> {
        int num_cards = 2;

        void on_pick(const pick_card_args &args);
    };

    struct request_tornado : picking_request_allowing<card_pile_type::player_hand> {
        void on_pick(const pick_card_args &args);
    };

    struct request_poker : picking_request_allowing<card_pile_type::player_hand, card_pile_type::selection> {
        int num_cards = 2;

        void on_pick(const pick_card_args &args);
    };

    struct request_saved : picking_request_allowing<card_pile_type::player_hand, card_pile_type::main_deck> {
        player *saved = nullptr;

        void on_pick(const pick_card_args &args);
    };

    struct request_add_cube : picking_request_allowing<card_pile_type::player_character, card_pile_type::player_table> {
        int ncubes = 1;
        
        void on_pick(const pick_card_args &args);
    };

    struct request_move_bomb : picking_request_allowing<card_pile_type::player> {
        void on_pick(const pick_card_args &args);
    };

    struct request_rust : request_base {
        void on_resolve();
    };

    DEFINE_ENUM_TYPES_IN_NS(banggame, request_type,
        (none,          request_base)
        (predraw,       request_predraw)
        (check,         request_check)
        (generalstore,  request_generalstore)
        (discard,       request_discard)
        (discard_pass,  request_discard_pass)
        (bang,          request_bang)
        (duel,          request_damaging)
        (indians,       request_damaging)
        (destroy,       request_destroy)
        (steal,         request_steal)
        (death,         request_death)
        (bandidos,      request_bandidos)
        (tornado,       request_tornado)
        (poker,         request_poker)
        (saved,         request_saved)
        (add_cube,      request_add_cube)
        (move_bomb,     request_move_bomb)
        (rust,          request_rust)
        (shopchoice,    request_base)
        (kit_carlson,   request_kit_carlson)
        (claus_the_saint, request_claus_the_saint)
        (vera_custer,   request_vera_custer)
        (youl_grinner,  request_youl_grinner)
        (dutch_will,    request_dutch_will)
        (shop_choose_target, request_shop_choose_target)
        (lemonade_jim,  timer_lemonade_jim)
        (al_preacher,   timer_al_preacher)
        (damaging,      timer_damaging)
        (bush,          timer_bush)
    )

    template<request_type E> concept picking_request = requires (enums::enum_type_t<E> &req, card_pile_type pile, const pick_card_args &args) {
        { enums::enum_type_t<E>::valid_pile(pile) } -> std::convertible_to<bool>;
        req.on_pick(args);
    };

    template<request_type E> concept resolvable_request = requires (enums::enum_type_t<E> &req) {
        req.on_resolve();
    };

    template<request_type E> concept timer_request = std::derived_from<enums::enum_type_t<E>, timer_base>;

    struct request_holder : enums::enum_variant<request_type> {
        using enums::enum_variant<request_type>::enum_variant;
        
        template<request_type E> request_holder(enums::enum_constant<E> tag, int origin_card_id, player *origin, player *target, effect_flags flags)
            : enums::enum_variant<request_type>(tag) {
            auto &obj = get<E>();
            obj.origin_card_id = origin_card_id;
            obj.origin = origin;
            obj.target = target;
            obj.flags = flags;
        }

        int origin_card_id() const {
            return enums::visit(&request_base::origin_card_id, *this);
        }

        player *origin() const {
            return enums::visit(&request_base::origin, *this);
        }

        player *target() const {
            return enums::visit(&request_base::target, *this);
        }

        effect_flags flags() const {
            return enums::visit(&request_base::flags, *this);
        }
    };

}
#endif