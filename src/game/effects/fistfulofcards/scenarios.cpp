#include "scenarios.h"

#include "../base/requests.h"

#include "../../game.h"

namespace banggame {
    using namespace enums::flag_operators;

    void effect_ambush::on_equip(card *target_card, player *target) {
        for (auto &p : target->m_game->m_players) {
            p.add_player_flags(player_flags::disable_player_distances);
        }
    }

    void effect_ambush::on_unequip(card *target_card, player *target) {
        for (auto &p : target->m_game->m_players) {
            p.remove_player_flags(player_flags::disable_player_distances);
        }
    }

    void effect_sniper::on_play(card *origin_card, player *origin, player *target) {
        auto req = std::make_shared<request_bang>(origin_card, origin, target);
        req->bang_strength = 2;
        target->m_game->queue_request(std::move(req));
    }

    void effect_startofturn::verify(card *origin_card, player *origin) const {
        if (!origin->check_player_flags(player_flags::start_of_turn)) {
            throw game_error("ERROR_NOT_START_OF_TURN");
        }
    }

    void effect_deadman::on_equip(card *target_card, player *target) {
        target->m_game->m_scenario_flags |= scenario_flags::deadman;
    }

    void effect_judge::on_equip(card *target_card, player *target) {
        target->m_game->m_scenario_flags |= scenario_flags::judge;
    }

    void effect_lasso::on_equip(card *target_card, player *target) {
        target->m_game->add_disabler(target_card, [](card *c) {
            return c->pocket == pocket_type::player_table;
        });
    }

    void effect_lasso::on_unequip(card *target_card, player *target) {
        target->m_game->remove_disablers(target_card);
    }

    void effect_abandonedmine::on_equip(card *target_card, player *target) {
        target->m_game->m_scenario_flags |= scenario_flags::abandonedmine;
    }

    void effect_peyote::on_equip(card *target_card, player *target) {
        target->m_game->add_event<event_type::on_request_draw>(target_card, [=](player *p) {
            auto &vec = p->m_game->m_hidden_deck;
            for (auto it = vec.begin(); it != vec.end(); ) {
                auto *card = *it;
                if (card->responses.first_is(effect_type::peyotechoice)) {
                    it = p->m_game->move_card(card, pocket_type::selection, nullptr, show_card_flags::instant);
                } else {
                    ++it;
                }
            }
            
            p->m_game->queue_request<request_peyote>(target_card, p);
        });
    }

    void request_peyote::on_pick(pocket_type pocket, player *target_player, card *target_card) {
        auto *drawn_card = target->m_game->m_deck.back();
        target->m_game->send_card_update(drawn_card, nullptr, show_card_flags::short_pause);

        if ((target_card->responses.front().effect_value == 1)
            ? (drawn_card->sign.suit == card_suit::hearts || drawn_card->sign.suit == card_suit::diamonds)
            : (drawn_card->sign.suit == card_suit::clubs || drawn_card->sign.suit == card_suit::spades))
        {
            target->m_game->draw_card_to(pocket_type::player_hand, target);
        } else {
            target->m_game->draw_card_to(pocket_type::discard_pile);

            while (!target->m_game->m_selection.empty()) {
                target->m_game->move_card(target->m_game->m_selection.front(), pocket_type::hidden_deck, nullptr, show_card_flags::instant);
            }
            target->m_game->pop_request<request_peyote>();
            target->m_game->call_event<event_type::post_draw_cards>(target);
        }
    }

    game_formatted_string request_peyote::status_text(player *owner) const {
        if (target == owner) {
            return {"STATUS_PEYOTE", origin_card};
        } else {
            return {"STATUS_PEYOTE_OTHER", target, origin_card};
        }
    }

    void effect_ricochet::on_play(card *origin_card, player *origin, player *target, card *target_card) {
        target->m_game->queue_request<request_ricochet>(origin_card, origin, target, target_card);
    }

    game_formatted_string request_ricochet::status_text(player *owner) const {
        if (target == owner) {
            return {"STATUS_RICOCHET", origin_card, target_card};
        } else {
            return {"STATUS_RICOCHET_OTHER", target, origin_card, target_card};
        }
    }

    void effect_russianroulette::on_equip(card *target_card, player *target) {
        auto queue_russianroulette_request = [=](player *target) {
            auto req = std::make_shared<request_bang>(target_card, nullptr, target);
            req->bang_damage = 2;
            target->m_game->queue_request(std::move(req));
        };
        queue_russianroulette_request(target);
        target->m_game->add_event<event_type::on_missed>(target_card, [=](card *origin_card, player *origin, player *target, bool is_bang) {
            if (target_card == origin_card) {
                queue_russianroulette_request(target->m_game->get_next_player(target));
            }
        });
        target->m_game->add_event<event_type::on_hit>(target_card, [=](card *origin_card, player *origin, player *target, int damage, bool is_bang) {
            if (target_card == origin_card) {
                target->m_game->remove_events(target_card);
            }
        });
    }

    void effect_fistfulofcards::on_equip(card *target_card, player *target) {
        target->m_game->add_event<event_type::pre_turn_start>(target_card, [=](player *p) {
            for (int i=0; i<p->m_hand.size(); ++i) {
                p->m_game->queue_request<request_bang>(target_card, nullptr, p);
            }
        });
    }

    void effect_lawofthewest::on_equip(card *target_card, player *target) {
        target->m_game->add_event<event_type::on_card_drawn>(target_card, [](player *origin, card *drawn_card) {
            if (origin->m_num_drawn_cards == 2) {
                origin->m_game->queue_action([=]{
                    origin->m_game->send_card_update(drawn_card, origin, show_card_flags::shown | show_card_flags::short_pause);
                    origin->m_game->send_card_update(drawn_card, origin);

                    if (origin->is_possible_to_play(drawn_card)) {
                        origin->set_mandatory_card(drawn_card);
                    }
                });
            }
        });
    }

    void effect_vendetta::on_equip(card *target_card, player *p) {
        p->m_game->add_event<event_type::post_turn_end>({target_card, 2}, [target_card](player *target) {
            target->m_game->queue_action([target, target_card] {
                target->m_game->draw_check_then(target, target_card, [target](card *drawn_card) {
                    if (target->get_card_sign(drawn_card).suit == card_suit::hearts) {
                        ++target->m_extra_turns;
                    }
                });
            });
        });
    }
}