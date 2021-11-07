#include "common/effects.h"
#include "common/requests.h"

#include "player.h"
#include "game.h"

namespace banggame {

    using namespace enums::flag_operators;

    void effect_bang::on_play(card *origin_card, player *origin, player *target) {
        target->m_game->queue_request<request_type::bang>(origin_card, origin, target, flags);
    }

    void effect_bangcard::on_play(card *origin_card, player *origin, player *target) {
        target->m_game->queue_event<event_type::on_play_bang>(origin);
        target->m_game->queue_event<event_type::delayed_action>([=]{
            request_bang req{origin_card, origin, target};
            req.is_bang_card = true;
            origin->apply_bang_mods(req);
            origin->m_game->queue_request(std::move(req));
        });
    }

    void effect_aim::on_play(card *origin_card, player *origin) {
        origin->add_bang_mod([](request_bang &req) {
            ++req.bang_damage;
        });
    }

    bool effect_missed::can_respond(player *origin) const {
        if (origin->m_game->top_request_is(request_type::bang, origin)) {
            auto &req = origin->m_game->top_request().get<request_type::bang>();
            return !req.unavoidable;
        }
        return false;
    }

    void effect_missed::on_play(card *origin_card, player *origin) {
        auto &req = origin->m_game->top_request().get<request_type::bang>();
        if (0 == --req.bang_strength) {
            origin->m_game->instant_event<event_type::on_missed>(req.origin, req.target, req.is_bang_card);
            origin->m_game->pop_request();
        }
    }

    bool effect_missedcard::can_respond(player *origin) const {
        return !origin->m_cant_play_missedcard && effect_missed().can_respond(origin);
    }

    bool effect_barrel::can_respond(player *origin) const {
        return effect_missed().can_respond(origin);
    }

    void effect_barrel::on_play(card *origin_card, player *target) {
        auto &req = target->m_game->top_request().get<request_type::bang>();
        if (std::ranges::find(req.barrels_used, origin_card) == std::ranges::end(req.barrels_used)) {
            req.barrels_used.push_back(origin_card);
            target->m_game->draw_check_then(target, [=](card_suit_type suit, card_value_type) {
                if (suit == card_suit_type::hearts) {
                    effect_missed().on_play(origin_card, target);
                }
            });
        }
    }

    bool effect_banglimit::can_play(card *origin_card, player *origin) const {
        return origin->can_play_bang();
    }

    void effect_banglimit::on_play(card *origin_card, player *origin) {
        ++origin->m_bangs_played;
    }

    void effect_indians::on_play(card *origin_card, player *origin, player *target) {
        target->m_game->queue_request<request_type::indians>(origin_card, origin, target, flags);
    }

    void effect_duel::on_play(card *origin_card, player *origin, player *target) {
        target->m_game->queue_request<request_type::duel>(origin_card, origin, target, flags);
    }

    bool effect_bangresponse::can_respond(player *origin) const {
        return origin->m_game->top_request_is(request_type::duel, origin)
            || origin->m_game->top_request_is(request_type::indians, origin);
    }

    void effect_bangresponse::on_play(card *origin_card, player *target) {
        switch (target->m_game->top_request().enum_index()) {
        case request_type::duel: {
            card *origin_card = target->m_game->top_request().origin_card();
            player *origin = target->m_game->top_request().origin();
            target->m_game->pop_request_noupdate();
            target->m_game->queue_request<request_type::duel>(origin_card, target, origin);
            break;
        }
        case request_type::indians:
            target->m_game->pop_request();
        }
    }

    bool effect_bangresponse_onturn::can_respond(player *origin) const {
        return effect_bangresponse::can_respond(origin) && origin == origin->m_game->m_playing;
    }

    bool effect_bangmissed::can_respond(player *origin) const {
        return effect_missed().can_respond(origin) || effect_bangresponse().can_respond(origin);
    }

    void effect_bangmissed::on_play(card *origin_card, player *target) {
        switch (target->m_game->top_request().enum_index()) {
        case request_type::bang:
            effect_missed().on_play(origin_card, target);
            break;
        case request_type::duel:
        case request_type::indians:
            effect_bangresponse().on_play(origin_card, target);
            break;
        }
    }

    void effect_generalstore::on_play(card *origin_card, player *origin) {
        for (int i=0; i<origin->m_game->num_alive(); ++i) {
            origin->m_game->draw_card_to(card_pile_type::selection);
        }
        origin->m_game->queue_request<request_type::generalstore>(origin_card, origin, origin);
    }

    void effect_heal::on_play(card *origin_card, player *origin, player *target) {
        target->heal(1);
    }

    bool effect_damage::can_play(card *origin_card, player *origin, player *target) const {
        return target->m_hp > 1;
    }

    void effect_damage::on_play(card *origin_card, player *origin, player *target) {
        target->damage(origin_card, origin, 1);
    }

    void effect_beer::on_play(card *origin_card, player *origin, player *target) {
        target->m_game->queue_event<event_type::on_play_beer>(target);
        if (target->m_game->m_players.size() <= 2 || target->m_game->num_alive() > 2) {
            target->heal(target->m_beer_strength);
        }
    }

    bool effect_deathsave::can_respond(player *origin) const {
        if (origin->m_game->top_request_is(request_type::death, origin)) {
            auto &req = origin->m_game->top_request().get<request_type::death>();
            return req.draw_attempts.empty();
        }
        return false;
    }

    void effect_deathsave::on_play(card *origin_card, player *origin) {
        if (origin->m_hp > 0) {
            origin->m_game->pop_request();
        }
    }

    void effect_destroy::on_play(card *origin_card, player *origin, player *target, card *target_card) {
        if (origin != target && target->can_escape(origin_card, flags)) {
            target->m_game->queue_request(request_destroy{origin_card, origin, target, flags, target_card});
        } else {
            target->m_game->instant_event<event_type::on_discard_card>(origin, target, target_card);
            auto effect_end_pos = std::ranges::find(target->m_game->m_pending_events, enums::indexof(event_type::on_effect_end), &event_args::index);
            if (effect_end_pos == target->m_game->m_pending_events.end()) {
                target->discard_card(target_card);
            } else {
                target->m_game->m_pending_events.emplace(effect_end_pos, std::in_place_index<enums::indexof(event_type::delayed_action)>,
                [=]{
                    target->discard_card(target_card);
                });
            }
        }
    }

    void effect_steal::on_play(card *origin_card, player *origin, player *target, card *target_card) {
        if (origin != target && target->can_escape(origin_card, flags)) {
            target->m_game->queue_request(request_steal{origin_card, origin, target, flags, target_card});
        } else {
            target->m_game->instant_event<event_type::on_discard_card>(origin, target, target_card);
            auto effect_end_pos = std::ranges::find(target->m_game->m_pending_events, enums::indexof(event_type::on_effect_end), &event_args::index);
            if (effect_end_pos == target->m_game->m_pending_events.end()) {
                origin->steal_card(target, target_card);
            } else {
                target->m_game->m_pending_events.emplace(effect_end_pos, std::in_place_index<enums::indexof(event_type::delayed_action)>,
                [=]{
                    origin->steal_card(target, target_card);
                });
            }
        }
    }

    void effect_virtual_destroy::on_play(card *origin_card, player *origin, player *target, card *target_card) {
        target->m_virtual.emplace(target_card, *target->discard_card(target_card));
    }

    void effect_virtual_copy::on_play(card *origin_card, player *origin, player *target, card *target_card) {
        target->m_virtual.emplace(target_card, *target_card);
        target->m_virtual->virtual_card.suit = card_suit_type::none;
        target->m_virtual->virtual_card.value = card_value_type::none;
    }

    void effect_virtual_clear::on_play(card *origin_card, player *origin) {
        origin->m_virtual.reset();
    }

    void effect_draw::on_play(card *origin_card, player *origin, player *target) {
        target->m_game->draw_card_to(card_pile_type::player_hand, target);
    }

    bool effect_draw_discard::can_play(card *origin_card, player *origin, player *target) const {
        return ! target->m_game->m_discards.empty();
    }

    void effect_draw_discard::on_play(card *origin_card, player *origin, player *target) {
        target->add_to_hand(target->m_game->draw_from_discards());
    }

    void effect_draw_rest::on_play(card *origin_card, player *target) {
        for (; target->m_num_drawn_cards<target->m_num_cards_to_draw; ++target->m_num_drawn_cards) {
            target->m_game->draw_card_to(card_pile_type::player_hand, target);
        }
    }

    void effect_draw_done::on_play(card *origin_card, player *target) {
        target->m_num_drawn_cards = target->m_num_cards_to_draw;
    }

    bool effect_draw_skip::can_play(card *origin_card, player *target) const {
        return target->m_num_drawn_cards < target->m_num_cards_to_draw;
    }

    void effect_draw_skip::on_play(card *origin_card, player *target) {
        ++target->m_num_drawn_cards;
    }

    void effect_bandidos::on_play(card *origin_card, player *origin, player *target) {
        target->m_game->queue_request<request_type::bandidos>(origin_card, origin, target, flags);
    }

    void effect_tornado::on_play(card *origin_card, player *origin, player *target) {
        if (target->num_hand_cards() == 0) {
            target->m_game->queue_event<event_type::delayed_action>([=]{
                target->m_game->draw_card_to(card_pile_type::player_hand, target);
                target->m_game->draw_card_to(card_pile_type::player_hand, target);
            });
        } else {
            target->m_game->queue_request<request_type::tornado>(origin_card, origin, target);
        }
    }

    void effect_poker::on_play(card *origin_card, player *origin) {
        auto target = origin;
        while(true) {
            target = origin->m_game->get_next_player(target);
            if (target == origin) break;
            if (!target->m_hand.empty()) {
                origin->m_game->queue_request<request_type::poker>(origin_card, origin, target, flags);
            }
        };
        origin->m_game->queue_event<event_type::delayed_action>([=]{
            if (std::ranges::find(origin->m_game->m_selection, card_value_type::value_A, &card::value) != origin->m_game->m_selection.end()) {
                for (auto &c : target->m_game->m_selection) {
                    origin->m_game->move_to(std::move(c), card_pile_type::discard_pile);
                }
                origin->m_game->m_selection.clear();
            } else if (origin->m_game->m_selection.size() <= 2) {
                for (auto &c : origin->m_game->m_selection) {
                    origin->add_to_hand(std::move(c));
                }
                origin->m_game->m_selection.clear();
            } else {
                origin->m_game->queue_request<request_type::poker_draw>(origin_card, origin, origin);
            }
        });
    }

    bool effect_saved::can_respond(player *origin) const {
        if (origin->m_game->top_request_is(request_type::damaging)) {
            auto &t = origin->m_game->top_request().get<request_type::damaging>();
            return t.target != origin;
        }
        return false;
    }

    void effect_saved::on_play(card *origin_card, player *origin) {
        auto &timer = origin->m_game->top_request().get<request_type::damaging>();
        player *saved = timer.target;
        if (0 == --timer.damage) {
            origin->m_game->pop_request();
        }
        origin->m_game->queue_event<event_type::delayed_action>([=]{
            if (saved->alive()) {
                origin->m_game->queue_request<request_type::saved>(origin_card, origin, origin).saved = saved;
            }
        });
    }

    bool effect_escape::can_respond(player *origin) const {
        return !origin->m_game->m_requests.empty()
            && bool(origin->m_game->top_request().flags() & effect_flags::escapable);
    }

    void effect_escape::on_play(card *origin_card, player *origin) {
        origin->m_game->pop_request();
    }

    struct rum_check_handler {
        player *origin;

        std::array<card_suit_type, 4> checks;
        int count_checks;

        void operator()(card_suit_type suit, card_value_type value) {
            if (count_checks < 3) {
                checks[count_checks++] = suit;
                origin->m_game->draw_check_then(origin, std::move(*this), true);
            } else {
                origin->heal(std::distance(checks.begin(), std::unique(checks.begin(), checks.end())));
            }
        }
    };

    void effect_rum::on_play(card *origin_card, player *origin) {
        origin->m_game->draw_check_then(origin, rum_check_handler{origin}, true);
    }

    void effect_goldrush::on_play(card *origin_card, player *origin) {
        origin->m_game->m_next_turn = origin;
        origin->pass_turn();
        origin->m_game->queue_event<event_type::delayed_action>([=] {
            origin->heal(origin->m_max_hp);
        });
    }

    static void swap_shop_choice_in(card *origin_card, player *origin, effect_type type) {
        for (auto &c : origin->m_game->m_shop_selection) {
            origin->m_game->move_to(std::move(c), card_pile_type::shop_hidden, true, nullptr, show_card_flags::no_animation);
        }
        origin->m_game->m_shop_selection.clear();

        auto &vec = origin->m_game->m_shop_hidden;
        for (auto it = vec.begin(); it != vec.end(); ) {
            auto *card = *it;
            if (!card->responses.empty() && card->responses.front().is(type)) {
                origin->m_game->move_to(card, card_pile_type::shop_selection, true, nullptr, show_card_flags::no_animation);
                it = vec.erase(it);
            } else {
                ++it;
            }
        }

        origin->m_game->queue_request<request_type::shopchoice>(origin_card, nullptr, origin);
    }

    void effect_bottle::on_play(card *origin_card, player *origin) {
        swap_shop_choice_in(origin_card, origin, effect_type::bottlechoice);
    }

    void effect_pardner::on_play(card *origin_card, player *origin) {
        swap_shop_choice_in(origin_card, origin, effect_type::pardnerchoice);
    }

    bool effect_shopchoice::can_respond(player *origin) const {
        return origin->m_game->top_request_is(request_type::shopchoice, origin);
    }

    void effect_shopchoice::on_play(card *origin_card, player *origin) {
        int n_choice = origin->m_game->m_shop_selection.size();
        for (auto &c : origin->m_game->m_shop_selection) {
            origin->m_game->move_to(std::move(c), card_pile_type::shop_hidden, true, nullptr, show_card_flags::no_animation);
        }
        origin->m_game->m_shop_selection.clear();

        auto end = origin->m_game->m_shop_hidden.end() - n_choice;
        auto begin = end - 2;
        for (auto it = begin; it != end; ++it) {
            origin->m_game->move_to(std::move(*it), card_pile_type::shop_selection, true, nullptr, show_card_flags::no_animation);
        }
        origin->m_game->m_shop_hidden.erase(begin, end);
        origin->m_game->pop_request();
        origin->m_game->queue_event<event_type::delayed_action>([m_game = origin->m_game]{
            while (m_game->m_shop_selection.size() < 3) {
                m_game->draw_shop_card();
            }
        });
    }

    bool effect_pay_cube::can_play(card *origin_card, player *origin, player *target, card *target_card) const {
        return target_card->cubes.size() >= std::max(1, args);
    }

    void effect_pay_cube::on_play(card *origin_card, player *origin, player *target, card *target_card) {
        target->pay_cubes(target_card, std::max(1, args));
    }

    void effect_add_cube::on_play(card *origin_card, player *origin, player *target, card *target_card) {
        target->add_cubes(target_card, std::max(1, args));
    }

    void effect_reload::on_play(card *origin_card, player *origin) {
        if (origin->can_receive_cubes()) {
            origin->m_game->queue_request<request_type::add_cube>(origin_card, nullptr, origin).ncubes = 3;
        }
    }
    
    void effect_rust::on_play(card *origin_card, player *origin, player *target) {
        if (target->can_escape(origin_card, flags)) {
            origin->m_game->queue_request<request_type::rust>(origin_card, origin, target, flags);
        } else {
            target->m_game->queue_event<event_type::delayed_action>([=]{
                target->move_cubes(target->m_characters.front(), origin->m_characters.front(), 1);
                for (auto &c : target->m_table | std::views::reverse) {
                    if (c->color == card_color_type::orange) {
                        target->move_cubes(c, origin->m_characters.front(), 1);
                    }
                }
            });
        }
    }

    bool effect_bandolier::can_play(card *origin_card, player *origin) const {
        return origin->m_bangs_played > 0 && origin->m_bangs_per_turn == 1;
    }

    void effect_bandolier::on_play(card *origin_card, player *origin) {
        origin->m_bangs_per_turn = 2;
    }

    bool effect_belltower::can_play(card *origin_card, player *origin) const {
        return origin->m_belltower == 0;
    }

    void effect_belltower::on_play(card *origin_card, player *origin) {
        ++origin->m_belltower;
    }

    void effect_doublebarrel::on_play(card *origin_card, player *origin) {
        origin->add_bang_mod([=](request_bang &req) {
            if (req.origin_card->suit == card_suit_type::diamonds) {
                req.unavoidable = true;
            }
        });
    }

    static void erase_from_deck_or_discards(game *game, card *card) {
        if (auto it = std::ranges::find(game->m_discards | std::views::reverse, card); it != game->m_discards.rend()) {
            game->m_discards.erase(it.base());
        } else if (auto it = std::ranges::find(game->m_deck, card); it != game->m_deck.end()) {
            game->m_deck.erase(it);
        }
    }

    void effect_thunderer::on_play(card *origin_card, player *origin) {
        origin->add_bang_mod([=](request_bang &req) {
            req.cleanup_function = [=]{
                card *bang_card = origin->m_virtual ? origin->m_virtual->corresponding_card : req.origin_card;
                origin->add_to_hand(bang_card);
                erase_from_deck_or_discards(origin->m_game, bang_card);
            };
        });
    }

    void effect_buntlinespecial::on_play(card *origin_card, player *p) {
        p->add_bang_mod([=](request_bang &req) {
            p->m_game->add_event<event_type::on_missed>(origin_card, [=](player *origin, player *target, bool is_bang) {
                if (target && origin == p && is_bang && !target->m_hand.empty()) {
                    target->m_game->queue_request<request_type::discard>(origin_card, origin, target);
                }
            });
            req.cleanup_function = [=]{
                p->m_game->remove_events(origin_card);
            };
        });
    }

    void effect_bigfifty::on_play(card *origin_card, player *p) {
        p->m_game->disable_table_cards(true);
        p->add_bang_mod([p](request_bang &req) {
            req.cleanup_function = [p]{
                p->m_game->enable_table_cards(true);
            };
        });
    }

    void effect_flintlock::on_play(card *origin_card, player *p) {
        p->m_game->add_event<event_type::on_missed>(origin_card, [=](player *origin, player *target, bool is_bang) {
            if (origin == p) {
                origin->m_game->move_to(origin_card, card_pile_type::player_hand, true, origin);
                erase_from_deck_or_discards(origin->m_game, origin_card);
            }
        });
        p->m_game->top_request().get<request_type::bang>().cleanup_function = [=]{
            p->m_game->remove_events(origin_card);
        };
    }

    void effect_duck::on_play(card *origin_card, player *origin) {
        origin->m_game->move_to(origin_card, card_pile_type::player_hand, true, origin);
        erase_from_deck_or_discards(origin->m_game, origin_card);
    }

    struct squaw_handler {
        card *origin_card;
        player *origin;
        player *target;
        card *target_card;
        effect_flags flags;
        bool steal;

        void operator()(player *p, card *c) {
            if (p == origin && c == origin_card) {
                origin->m_game->remove_events(origin_card);
                if (steal) {
                    effect_steal e;
                    e.flags = flags;
                    e.on_play(origin_card, origin, target, target_card);
                } else {
                    effect_destroy e;
                    e.flags = flags;
                    e.on_play(origin_card, origin, target, target_card);
                }
            }
        }
    };

    void effect_squaw_destroy::on_play(card *origin_card, player *origin, player *target, card *target_card) {
        origin->m_game->add_event<event_type::on_play_card_end>(origin_card,
            squaw_handler{origin_card, origin, target, target_card, flags, false});
    }

    void effect_squaw_steal::on_play(card *origin_card, player *origin) {
        origin->m_game->m_event_handlers.find(origin_card)->second
            .get<event_type::on_play_card_end>().target<squaw_handler>()->steal = true;
    }

    void effect_tumbleweed::on_equip(player *origin, card *target_card) {
        origin->m_game->add_event<event_type::trigger_tumbleweed>(target_card, [=](card_suit_type suit, card_value_type value) {
            auto &req = origin->m_game->add_request<request_type::tumbleweed>(target_card, origin, origin);
            req.suit = suit;
            req.value = value;
            origin->m_game->m_current_check->no_auto_resolve = true;
        });
    }

    bool effect_tumbleweed::can_respond(player *origin) const {
        return origin->m_game->top_request_is(request_type::tumbleweed);
    }

    void effect_tumbleweed::on_play(card *origin_card, player *origin) {
        origin->m_game->pop_request();
        origin->m_game->do_draw_check();
    }

    void timer_tumbleweed::on_finished() {
        origin->m_game->pop_request();
        origin->m_game->m_current_check->function(suit, value);
        origin->m_game->m_current_check.reset();
    }

}