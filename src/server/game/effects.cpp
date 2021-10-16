#include "common/effects.h"
#include "common/requests.h"

#include "player.h"
#include "game.h"

namespace banggame {

    void effect_bang::on_play(int origin_card_id, player *origin, player *target) {
        target->m_game->queue_request<request_type::bang>(origin_card_id, origin, target, flightable);
    }

    void effect_bangcard::on_play(int origin_card_id, player *origin, player *target) {
        target->m_game->queue_event<event_type::on_play_bang>(origin);
        target->m_game->queue_event<event_type::delayed_action>([=]{
            request_bang req{origin_card_id, origin, target};
            req.is_bang_card = true;
            origin->apply_bang_mods(req);
            origin->m_game->queue_request(std::move(req));
        });
    }

    void effect_aim::on_play(int origin_card_id, player *origin) {
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

    void effect_missed::on_play(int origin_card_id, player *origin) {
        auto &req = origin->m_game->top_request().get<request_type::bang>();
        if (0 == --req.bang_strength) {
            origin->m_game->pop_request();
        }
    }

    bool effect_missedcard::can_respond(player *origin) const {
        return !origin->m_cant_play_missedcard && effect_missed().can_respond(origin);
    }

    bool effect_barrel::can_respond(player *origin) const {
        return effect_missed().can_respond(origin);
    }

    void effect_barrel::on_play(int card_id, player *target) {
        auto &req = target->m_game->top_request().get<request_type::bang>();
        if (std::ranges::find(req.barrels_used, card_id) == std::ranges::end(req.barrels_used)) {
            req.barrels_used.push_back(card_id);
            target->m_game->draw_check_then(target, [=](card_suit_type suit, card_value_type) {
                if (suit == card_suit_type::hearts) {
                    effect_missed().on_play(card_id, target);
                }
            });
        }
    }

    bool effect_banglimit::can_play(player *target) const {
        return target->can_play_bang();
    }

    void effect_banglimit::on_play(int origin_card_id, player *origin) {
        ++origin->m_bangs_played;
    }

    void effect_indians::on_play(int origin_card_id, player *origin, player *target) {
        target->m_game->queue_request<request_type::indians>(origin_card_id, origin, target, flightable);
    }

    void effect_duel::on_play(int origin_card_id, player *origin, player *target) {
        target->m_game->queue_request<request_type::duel>(origin_card_id, origin, target, flightable);
    }

    bool effect_bangresponse::can_respond(player *origin) const {
        return origin->m_game->top_request_is(request_type::duel, origin)
            || origin->m_game->top_request_is(request_type::indians, origin);
    }

    void effect_bangresponse::on_play(int origin_card_id, player *target) {
        switch (target->m_game->top_request().enum_index()) {
        case request_type::duel: {
            int origin_card_id = target->m_game->top_request().origin_card_id();
            player *origin = target->m_game->top_request().origin();
            target->m_game->pop_request_noupdate();
            target->m_game->queue_request<request_type::duel>(origin_card_id, target, origin);
            break;
        }
        case request_type::indians:
            target->m_game->pop_request();
        }
    }

    bool effect_bangmissed::can_respond(player *origin) const {
        return effect_missed().can_respond(origin) || effect_bangresponse().can_respond(origin);
    }

    void effect_bangmissed::on_play(int origin_card_id, player *target) {
        switch (target->m_game->top_request().enum_index()) {
        case request_type::bang:
            effect_missed().on_play(origin_card_id, target);
            break;
        case request_type::duel:
        case request_type::indians:
            effect_bangresponse().on_play(origin_card_id, target);
            break;
        }
    }

    void effect_generalstore::on_play(int origin_card_id, player *origin) {
        for (int i=0; i<origin->m_game->num_alive(); ++i) {
            origin->m_game->add_to_selection(origin->m_game->draw_card());
        }
        origin->m_game->queue_request<request_type::generalstore>(origin_card_id, origin, origin);
    }

    void effect_heal::on_play(int origin_card_id, player *origin, player *target) {
        target->heal(1);
    }

    bool effect_damage::can_play(player *target) const {
        return target->m_hp > 1;
    }

    void effect_damage::on_play(int origin_card_id, player *origin, player *target) {
        target->do_damage(origin_card_id, origin, 1);
    }

    void effect_beer::on_play(int origin_card_id, player *origin, player *target) {
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

    void effect_deathsave::on_play(int origin_card_id, player *origin) {
        if (origin->m_hp > 0) {
            origin->m_game->pop_request();
        }
    }

    void effect_destroy::on_play(int origin_card_id, player *origin, player *target, int card_id) {
        if (flightable && origin != target) {
            auto &req = target->m_game->queue_request<request_type::destroy>(origin_card_id, origin, target, true);
            req.card_id = card_id;
        } else {
            target->m_game->queue_event<event_type::on_discard_card>(origin, target, card_id);
            target->m_game->queue_event<event_type::delayed_action>([=]{
                target->discard_card(card_id);
            });
        }
    }

    void effect_steal::on_play(int origin_card_id, player *origin, player *target, int card_id) {
        if (flightable && origin != target) {
            auto &req = target->m_game->queue_request<request_type::steal>(origin_card_id, origin, target, true);
            req.card_id = card_id;
        } else {
            target->m_game->queue_event<event_type::on_discard_card>(origin, target, card_id);
            target->m_game->queue_event<event_type::delayed_action>([=]{
                origin->steal_card(target, card_id);
            });
        }
    }

    void effect_virtual_destroy::on_play(int origin_card_id, player *origin, player *target, int card_id) {
        target->m_virtual = std::make_pair(card_id, target->discard_card(card_id));
    }

    void effect_virtual_copy::on_play(int origin_card_id, player *origin, player *target, int card_id) {
        auto copy = target->find_card(card_id);
        copy.suit = card_suit_type::none;
        copy.value = card_value_type::none;
        target->m_virtual = std::make_pair(card_id, std::move(copy));
    }

    void effect_virtual_clear::on_play(int origin_card_id, player *origin) {
        origin->m_virtual.reset();
    }

    void effect_draw::on_play(int origin_card_id, player *origin, player *target) {
        target->add_to_hand(target->m_game->draw_card());
    }

    bool effect_draw_discard::can_play(player *target) const {
        return ! target->m_game->m_discards.empty();
    }

    void effect_draw_discard::on_play(int origin_card_id, player *origin, player *target) {
        target->add_to_hand(target->m_game->draw_from_discards());
    }

    void effect_draw_rest::on_play(int origin_card_id, player *target) {
        for (; target->m_num_drawn_cards<target->m_num_cards_to_draw; ++target->m_num_drawn_cards) {
            target->add_to_hand(target->m_game->draw_card());
        }
    }

    void effect_draw_done::on_play(int origin_card_id, player *target) {
        target->m_num_drawn_cards = target->m_num_cards_to_draw;
    }

    bool effect_draw_skip::can_play(player *target) const {
        return target->m_num_drawn_cards < target->m_num_cards_to_draw;
    }

    void effect_draw_skip::on_play(int origin_card_id, player *target) {
        ++target->m_num_drawn_cards;
    }

    void effect_bandidos::on_play(int origin_card_id, player *origin, player *target) {
        target->m_game->queue_request<request_type::bandidos>(origin_card_id, origin, target, flightable);
    }

    void effect_tornado::on_play(int origin_card_id, player *origin, player *target) {
        if (target->num_hand_cards() == 0) {
            target->m_game->queue_event<event_type::delayed_action>([=]{
                target->add_to_hand(target->m_game->draw_card());
                target->add_to_hand(target->m_game->draw_card());
            });
        } else {
            target->m_game->queue_request<request_type::tornado>(origin_card_id, origin, target);
        }
    }

    void effect_poker::on_play(int origin_card_id, player *origin) {
        auto next = origin;
        do {
            next = origin->m_game->get_next_player(next);
            if (next == origin) return;
        } while (next->m_hand.empty());
        origin->m_game->queue_request<request_type::poker>(origin_card_id, origin, next, flightable);
    }

    bool effect_saved::can_respond(player *origin) const {
        if (origin->m_game->top_request_is(request_type::damaging)) {
            auto &t = origin->m_game->top_request().get<request_type::damaging>();
            return t.target != origin;
        }
        return false;
    }

    void effect_saved::on_play(int origin_card_id, player *origin) {
        auto &timer = origin->m_game->top_request().get<request_type::damaging>();
        player *saved = timer.target;
        if (0 == --timer.damage) {
            origin->m_game->pop_request();
        }
        origin->m_game->queue_event<event_type::delayed_action>([=]{
            if (saved->alive()) {
                origin->m_game->queue_request<request_type::saved>(origin_card_id, origin, origin).saved = saved;
            }
        });
    }

    bool effect_flight::can_respond(player *origin) const {
        return !origin->m_game->m_requests.empty() && origin->m_game->top_request().flightable();
    }

    void effect_flight::on_play(int origin_card_id, player *origin) {
        origin->m_game->pop_request();
    }

    void effect_doublebarrel::on_play(int origin_card_id, player *origin) {
        origin->add_bang_mod([=](request_bang &req) {
            if (auto it = std::ranges::find(origin->m_game->m_discards | std::views::reverse, req.origin_card_id, &deck_card::id);
                it != origin->m_game->m_discards.rend() && it->suit == card_suit_type::diamonds) {
                req.unavoidable = true;
            }
        });
    }
}