#include "common/characters.h"
#include "common/effects.h"

#include "player.h"
#include "game.h"

namespace banggame {
    using namespace enums::flag_operators;

    void effect_slab_the_killer::on_equip(player *p, card *target_card) {
        p->m_game->add_event<event_type::on_play_bang>(target_card, [p](player *target) {
            if (p == target) {
                target->add_bang_mod([](request_bang &req) {
                    ++req.bang_strength;
                });
            }
        });
        ++p->m_buntline_ncards;
    }

    void effect_slab_the_killer::on_unequip(player *p, card *target_card) {
        event_based_effect::on_unequip(p, target_card);
        --p->m_buntline_ncards;
    }

    void effect_black_jack::on_play(card *origin_card, player *target) {
        int ncards = target->m_num_drawn_cards = target->m_num_cards_to_draw;
        for (int i=0; i<ncards; ++i) {
            if (i==1) {
                auto *drawn_card = target->m_game->m_deck.back();
                if (drawn_card->suit == card_suit_type::hearts || drawn_card->suit == card_suit_type::diamonds) {
                    ++ncards;
                }
                target->m_game->send_card_update(*drawn_card, nullptr, show_card_flags::short_pause);
                target->m_game->draw_card_to(card_pile_type::player_hand, target);
            } else {
                target->m_game->draw_card_to(card_pile_type::player_hand, target);
            }
        }
    }

    void effect_bill_noface::on_play(card *origin_card, player *target) {
        target->m_num_drawn_cards = target->m_num_cards_to_draw;
        int ncards = target->m_num_cards_to_draw - 1 + target->m_max_hp - target->m_hp;
        for (int i=0; i<ncards; ++i) {
            target->m_game->draw_card_to(card_pile_type::player_hand, target);
        }
    }

    void effect_tequila_joe::on_equip(player *target, card *target_card) {
        ++target->m_beer_strength;
    }

    void effect_tequila_joe::on_unequip(player *target, card *target_card) {
        --target->m_beer_strength;
    }

    void effect_kit_carlson::on_play(card *origin_card, player *target) {
        for (int i=0; i<=target->m_num_cards_to_draw; ++i) {
            target->m_game->draw_card_to(card_pile_type::selection, target);
        }
        target->m_game->queue_request<request_type::kit_carlson>(origin_card, target, target);
    }

    void request_kit_carlson::on_pick(card_pile_type pile, player *target_player, card *target_card) {
        target->add_to_hand(target_card);
        if (target->m_game->m_selection.size() == 1) {
            target->m_game->pop_request();
            target->m_game->move_to(target->m_game->m_selection.front(), card_pile_type::main_deck, false);
            target->m_num_drawn_cards = target->m_num_cards_to_draw;
        } else {
            target->m_game->pop_request_noupdate();
            target->m_game->queue_request<request_type::kit_carlson>(origin_card, target, target);
        }
    }

    void effect_claus_the_saint::on_play(card *origin_card, player *target) {
        target->m_num_drawn_cards = target->m_num_cards_to_draw;
        int ncards = target->m_game->num_alive() + target->m_num_cards_to_draw - 1;
        for (int i=0; i<ncards; ++i) {
            target->m_game->draw_card_to(card_pile_type::selection, target);
        }
        target->m_game->queue_request<request_type::claus_the_saint>(origin_card, target, target);
    }

    void request_claus_the_saint::on_pick(card_pile_type pile, player *target_player, card *target_card) {
        target->m_num_drawn_cards = target->m_num_cards_to_draw;
        int index = target->m_game->num_alive() + target->m_num_cards_to_draw - target->m_game->m_selection.size();
        auto p = target;
        for(int i=0; i<index; ++i) {
            p = target->m_game->get_next_player(p);
        }
        p->add_to_hand(target_card);
        if (target->m_game->m_selection.size() == target->m_num_cards_to_draw) {
            target->m_game->pop_request();
            while (!target->m_game->m_selection.empty()) {
                target->add_to_hand(target->m_game->m_selection.front());
            }
        } else {
            target->m_game->pop_request_noupdate();
            target->m_game->queue_request<request_type::claus_the_saint>(origin_card, target, target);
        }
    }

    void effect_el_gringo::on_equip(player *p, card *target_card) {
        p->m_game->add_event<event_type::on_hit>(target_card, [=](player *origin, player *target, int damage, bool is_bang) {
            if (origin && p == target && p->m_game->m_playing != p) {
                while(damage-- && !origin->m_hand.empty()) {
                    target->steal_card(origin, origin->random_hand_card());
                }
                target->m_game->queue_event<event_type::on_effect_end>(p, target_card);
            }
        });
    }

    void effect_suzy_lafayette::on_equip(player *p, card *target_card) {
        p->m_game->add_event<event_type::on_effect_end>(target_card, [p](player *origin, card *target_card) {
            if (p->m_hand.empty()) {
                p->m_game->draw_card_to(card_pile_type::player_hand, p);
            }
        });
    }

    void effect_vulture_sam::on_equip(player *p, card *target_card) {
        p->m_game->add_event<event_type::on_player_death>(target_card, [p](player *origin, player *target) {
            if (p != target) {
                for (auto it = target->m_table.begin(); it != target->m_table.end(); ) {
                    card *target_card = *it;
                    if (target_card->color != card_color_type::black) {
                        it = target->move_card_to(target_card, card_pile_type::player_hand, true, p);
                    } else {
                        ++it;
                    }
                }
                while (!target->m_hand.empty()) {
                    p->add_to_hand(target->m_hand.front());
                }
            }
        });
    }

    void effect_greg_digger::on_equip(player *p, card *target_card) {
        p->m_game->add_event<event_type::on_player_death>(target_card, [p](player *origin, player *target) {
            if (p != target) {
                p->heal(2);
            }
        });
    }

    void effect_herb_hunter::on_equip(player *p, card *target_card) {
        p->m_game->add_event<event_type::on_player_death>(target_card, [p](player *origin, player *target) {
            if (p != target) {
                p->m_game->draw_card_to(card_pile_type::player_hand, p);
                p->m_game->draw_card_to(card_pile_type::player_hand, p);
            }
        });
    }

    void effect_johnny_kisch::on_equip(player *p, card *target_card) {
        p->m_game->add_event<event_type::on_equip>(target_card, [p](player *origin, player *target, card *equipped_card) {
            if (p == origin) {
                const auto &name = equipped_card->name;
                for (auto &other : p->m_game->m_players) {
                    if (other.id == target->id) continue;
                    auto it = std::ranges::find(other.m_table, name, &card::name);
                    if (it != other.m_table.end()) {
                        other.discard_card(*it);
                    }
                }
            }
        });
    }

    void effect_molly_stark::on_equip(player *p, card *target_card) {
        p->m_game->add_event<event_type::on_play_hand_card>(target_card, [p](player *target, card *card) {
            if (p == target && p->m_game->m_playing != p) {
                p->m_game->draw_card_to(card_pile_type::player_hand, p);
            }
        });
    }

    void effect_bellestar::on_equip(player *p, card *target_card) {
        p->m_game->add_event<event_type::on_turn_start>(target_card, [p](player *target) {
            if (p == target) {
                p->m_game->disable_table_cards();
            }
        });
        p->m_game->add_event<event_type::on_turn_end>(target_card, [p](player *target) {
            if (p == target) {
                p->m_game->enable_table_cards();
            }
        });
        p->m_game->add_event<event_type::on_equip>(target_card, [p](player *origin, player *target, card *target_card) {
            if (origin == p && target != p) {
                target_card->on_unequip(target);
            }
        });
    }

    void effect_bellestar::on_unequip(player *target, card *target_card) {
        if (target == target->m_game->m_playing) {
            target->m_game->enable_table_cards();
        }
        target->m_game->remove_events(target_card);
    }

    static void vera_custer_copy_character(player *target, character *c) {
        if (c != target->m_characters.back()) {
            auto copy_it = target->m_game->m_characters.emplace(target->m_game->get_next_id(), *c).first;
            copy_it->second.id = copy_it->first;
            copy_it->second.usages = 0;

            if (target->m_characters.size() == 2) {
                target->m_characters.back()->on_unequip(target);
                target->m_game->m_characters.erase(target->m_characters.back()->id);
                target->m_characters.pop_back();
            }
            target->m_game->send_character_update(copy_it->second, target->id, 1);
            target->m_characters.emplace_back(&copy_it->second)->on_equip(target);
        }
    }

    void effect_vera_custer::on_equip(player *p, card *target_card) {
        p->m_game->add_event<event_type::on_turn_start>(target_card, [=](player *target) {
            if (p == target) {
                ++p->m_characters.front()->usages;
                if (p->m_game->num_alive() == 2 && p->m_game->get_next_player(p)->m_characters.size() == 1) {
                    vera_custer_copy_character(p, p->m_game->get_next_player(p)->m_characters.front());
                } else if (p->m_game->num_alive() > 2) {
                    p->m_game->queue_request<request_type::vera_custer>(target_card, target, target);
                }
            }
        });
        p->m_game->add_event<event_type::on_turn_end>(target_card, [p](player *target) {
            if (p == target && p->m_characters.front()->usages == 0) {
                if (p->m_characters.size() > 1) {
                    p->m_characters.back()->on_unequip(p);
                    p->m_characters.pop_back();
                    p->m_game->add_public_update<game_update_type::player_remove_character>(p->id, 1);
                }
            }
        });
        p->m_game->add_event<event_type::on_player_death>(target_card, [p](player *origin, player *target) {
            if (p == target && target->m_characters.size() > 1) {
                target->m_characters.pop_back();
                target->m_game->add_public_update<game_update_type::player_remove_character>(target->id, 1);
            }
        });
    }

    void request_vera_custer::on_pick(card_pile_type pile, player *target_player, card *target_card) {
        if (target_card != target->m_characters.front()) {
            target->m_game->pop_request();
            vera_custer_copy_character(target, static_cast<character *>(target_card));
        }
    }

    void effect_tuco_franziskaner::on_equip(player *p, card *target_card) {
        p->m_game->add_event<event_type::on_draw_from_deck>(target_card, [p](player *origin) {
            if (p == origin && std::ranges::find(p->m_table, card_color_type::blue, &card::color) == p->m_table.end()) {
                p->m_game->draw_card_to(card_pile_type::player_hand, p);
                p->m_game->draw_card_to(card_pile_type::player_hand, p);
            }
        });
    }

    void effect_colorado_bill::on_equip(player *p, card *target_card) {
        p->m_game->add_event<event_type::on_play_bang>(target_card, [p](player *origin) {
            if (p == origin) {
                origin->m_game->draw_check_then(origin, [=](card_suit_type suit, card_value_type) {
                    if (suit == card_suit_type::spades) {
                        origin->add_bang_mod([](request_bang &req) {
                            req.unavoidable = true;
                        });
                    }
                });
            }
        });
    }

    void effect_henry_block::on_equip(player *p, card *target_card) {
        p->m_game->add_event<event_type::on_discard_card>(target_card, [p](player *origin, player *target, card *target_card) {
            if (p == target && p != origin) {
                p->m_game->queue_request<request_type::bang>(target_card, target, origin);
            }
        });
    }

    void effect_big_spencer::on_equip(player *p, card *target_card) {
        p->m_cant_play_missedcard = true;
        p->m_initial_cards = 5;
    }

    void effect_big_spencer::on_unequip(player *p, card *target_card) {
        p->m_cant_play_missedcard = false;
        p->m_initial_cards = 0;
    }

    void effect_gary_looter::on_equip(player *p, card *target_card) {
        p->m_game->add_event<event_type::on_discard_pass>(target_card, [p](player *origin, card *discarded_card) {
            if (p != origin) {
                p->add_to_hand(discarded_card);
            }
        });
    }

    void effect_john_pain::on_equip(player *p, card *target_card) {
        p->m_game->add_event<event_type::on_draw_check>(target_card, [p](card *drawn_card) {
            if (p->m_hand.size() < 6) {
                p->add_to_hand(drawn_card);
            }
        });
    }

    bool effect_teren_kill::can_respond(card *origin_card, player *origin) const {
        if (origin->m_game->top_request_is(request_type::death, origin)) {
            const auto &vec = origin->m_game->top_request().get<request_type::death>().draw_attempts;
            return std::ranges::find(vec, origin_card) == vec.end();
        }
        return false;
    }

    void effect_teren_kill::on_play(card *origin_card, player *origin) {
        origin->m_game->top_request().get<request_type::death>().draw_attempts.push_back(origin_card);
        origin->m_game->draw_check_then(origin, [origin](card_suit_type suit, card_value_type) {
            if (suit != card_suit_type::spades) {
                origin->m_game->pop_request();
                origin->m_hp = 1;
                origin->m_game->add_public_update<game_update_type::player_hp>(origin->id, 1);
                origin->m_game->draw_card_to(card_pile_type::player_hand, origin);
            }
        });
    }

    void effect_youl_grinner::on_equip(player *target, card *target_card) {
        target->m_game->add_event<event_type::on_turn_start>(target_card, [=](player *origin) {
            if (target == origin) {
                for (auto &p : target->m_game->m_players) {
                    if (p.alive() && p.id != target->id && p.m_hand.size() > target->m_hand.size()) {
                        target->m_game->queue_request<request_type::youl_grinner>(target_card, target, &p);
                    }
                }
            }
        });
    }

    void request_youl_grinner::on_pick(card_pile_type pile, player *target_player, card *target_card) {
        if (target_player == target) {
            target->m_game->pop_request();
            origin->steal_card(target, target_card);
            target->m_game->queue_event<event_type::on_effect_end>(origin, origin_card);
        }
    }

    void effect_flint_westwood::on_play(card *origin_card, player *origin, player *target, card *target_card) {
        int num_cards = 2;
        for (int i=0; !target->m_hand.empty() && i<2; ++i) {
            origin->steal_card(target, target->random_hand_card());
        }
        target->steal_card(origin, origin->m_virtual->corresponding_card);
    }

    bool effect_lee_van_kliff::can_play(card *origin_card, player *origin, player *target, card *target_card) const {
        return origin->m_last_played_card
            && origin->m_last_played_card->color == card_color_type::brown
            && origin->m_last_played_card->expansion != card_expansion_type::goldrush;
    }

    void effect_lee_van_kliff::on_play(card *origin_card, player *origin, player *target, card *target_card) {
        auto copy = *origin->m_last_played_card;
        copy.suit = card_suit_type::none;
        copy.value = card_value_type::none;
        std::erase_if(copy.effects, [](const effect_holder &e) {
            return e.is(effect_type::banglimit);
        });
        origin->play_virtual_card(target_card, std::move(copy));
    }

    void effect_don_bell::on_equip(player *p, card *target_card) {
        p->m_game->add_event<event_type::on_turn_end>(target_card, [=](player *target) {
            if (p == target) {
                int &usages = static_cast<character *>(target_card)->max_usages;
                if (usages == 0) {
                    p->m_game->draw_check_then(p, [&](card_suit_type suit, card_value_type) {
                        if (suit == card_suit_type::diamonds || suit == card_suit_type::hearts) {
                            ++usages;
                            p->m_game->m_next_turn = p;
                        }
                    }, true);
                } else {
                    usages = 0;
                }
            }
        });
    }

    void effect_madam_yto::on_equip(player *p, card *target_card) {
        p->m_game->add_event<event_type::on_play_beer>(target_card, [p](player *target) {
            p->m_game->draw_card_to(card_pile_type::player_hand, p);
        });
    }

    static void greygory_deck_set_characters(player *target) {
        std::ranges::shuffle(target->m_game->m_base_characters, target->m_game->rng);
        for (int i=0; i<2; ++i) {
            auto *c = target->m_characters.emplace_back(target->m_game->m_base_characters[i]);
            c->on_equip(target);
            target->m_game->send_character_update(*c, target->id, i+1);
        }
    }

    void effect_greygory_deck::on_play(card *target_card, player *target) {
        int &usages = static_cast<character *>(target_card)->usages;
        if (usages == 0) {
            ++usages;

            for (int i=1; i<target->m_characters.size(); ++i) {
                target->m_characters[i]->on_unequip(target);
                target->m_game->m_characters.erase(target->m_characters[i]->id);
            }
            target->m_characters.resize(1);
            greygory_deck_set_characters(target);
        }
    }

    void effect_greygory_deck::on_equip(player *p, card *target_card) {
        p->m_game->add_event<event_type::on_game_start>(target_card, [p] {
            greygory_deck_set_characters(p);
        });
        p->m_game->add_event<event_type::on_player_death>(target_card, [p](player *origin, player *target) {
            if (p == target && target->m_characters.size() > 1) {
                target->m_characters.resize(1);
                target->m_game->add_public_update<game_update_type::player_remove_character>(target->id, 2);
                target->m_game->add_public_update<game_update_type::player_remove_character>(target->id, 1);
            }
        });
    }

    void effect_lemonade_jim::on_equip(player *origin, card *target_card) {
        origin->m_game->add_event<event_type::on_play_beer>(target_card, [=](player *target) {
            if (origin != target) {
                target->m_game->queue_request<request_type::lemonade_jim>(target_card, nullptr, origin).players.push_back(origin);
            }
        });
    }

    bool effect_lemonade_jim::can_respond(card *origin_card, player *target) const {
        if (target->m_game->top_request_is(request_type::lemonade_jim, target)) {
            const auto &vec = target->m_game->top_request().get<request_type::lemonade_jim>().players;
            return std::ranges::find(vec, target) == vec.end();
        }
        return false;
    }

    void effect_lemonade_jim::on_play(card *origin_card, player *origin, player *target) {
        target->heal(1);
        target->m_game->top_request().get<request_type::lemonade_jim>().players.push_back(target);
    }
    
    void effect_al_preacher::on_equip(player *p, card *target_card) {
        p->m_game->add_event<event_type::on_equip>(target_card, [=](player *origin, player *target, card *equipped_card) {
            if (p != origin) {
                if (equipped_card->color == card_color_type::blue || equipped_card->color == card_color_type::orange) {
                    p->m_game->queue_request<request_type::al_preacher>(target_card, nullptr, p);
                }
            }
        });
    }

    bool effect_al_preacher::can_respond(card *origin_card, player *target) const {
        if (target->m_game->top_request_is(request_type::al_preacher, target)) {
            const auto &vec = target->m_game->top_request().get<request_type::al_preacher>().players;
            return std::ranges::find(vec, target) == vec.end();
        }
        return false;
    }

    void effect_al_preacher::on_play(card *origin_card, player *target) {
        target->m_game->top_request().get<request_type::al_preacher>().players.push_back(target);
    }

    void effect_dutch_will::on_play(card *origin_card, player *target) {
        for (int i=0; i<target->m_num_cards_to_draw; ++i) {
            target->m_game->draw_card_to(card_pile_type::selection, target);
        }
        target->m_game->queue_request<request_type::dutch_will>(origin_card, target, target);
    }

    void request_dutch_will::on_pick(card_pile_type pile, player *target_player, card *target_card) {
        target->add_to_hand(target_card);
        if (target->m_game->m_selection.size() == 1) {
            target->m_game->pop_request();
            target->m_game->move_to(target->m_game->m_selection.front(), card_pile_type::discard_pile);
            target->add_gold(1);
            target->m_num_drawn_cards = target->m_num_cards_to_draw;
        }
    }

    void effect_josh_mccloud::on_play(card *origin_card, player *target) {
        using namespace enums::flag_operators;

        constexpr auto is_self_or_none = [](target_type type) {
            using namespace enums::flag_operators;
            return type == (target_type::self | target_type::player) || type == enums::flags_none<target_type>;
        };

        auto *card = target->m_game->draw_shop_card();
        switch (card->color) {
        case card_color_type::black:
            if (std::ranges::all_of(card->equips, is_self_or_none, &equip_holder::target)) {
                target->equip_card(card);
            } else {
                target->m_game->queue_request<request_type::shop_choose_target>(card, nullptr, target);
            }
            break;
        case card_color_type::brown:
            if (std::ranges::all_of(card->effects, is_self_or_none, &effect_holder::target)) {
                target->m_game->move_to(card, card_pile_type::shop_discard);
                for (auto &e : card->effects) {
                    switch(e.target()) {
                    case target_type::self | target_type::player:
                        e.on_play(card, target, target);
                        break;
                    case enums::flags_none<target_type>:
                        e.on_play(card, target);
                        break;
                    }
                }
            } else {
                target->m_game->queue_request<request_type::shop_choose_target>(card, nullptr, target);
            }
            break;
        }
    }

    void request_shop_choose_target::on_pick(card_pile_type pile, player *target_player, card *target_card) {
        target->m_game->pop_request();
        if (origin_card->color == card_color_type::black) {
            target_player->equip_card(origin_card);
        } else {
            target->m_game->move_to(origin_card, card_pile_type::shop_discard);
            for (auto &e : origin_card->effects) {
                e.on_play(origin_card, target, target_player);
            }
        }
    }

    void effect_julie_cutter::on_equip(player *p, card *target_card) {
        p->m_game->add_event<event_type::on_hit>(target_card, [=](player *origin, player *target, int damage, bool is_bang) {
            if (origin && p == target) {
                p->m_game->draw_check_then(target, [=](card_suit_type suit, card_value_type value) {
                    if (suit == card_suit_type::hearts || suit == card_suit_type::diamonds) {
                        p->m_game->queue_request<request_type::bang>(target_card, target, origin);
                    }
                });
            }
        });
    }

    bool effect_frankie_canton::can_play(card *origin_card, player *origin, player *target, card *target_card) const {
        return !target_card->cubes.empty();
    }

    void effect_frankie_canton::on_play(card *origin_card, player *origin, player *target, card *target_card) {
        target->move_cubes(target_card, origin->m_characters.front(), 1);
    }

    void effect_bloody_mary::on_equip(player *p, card *target_card) {
        p->m_game->add_event<event_type::on_missed>(target_card, [=](player *origin, player *target, bool is_bang) {
            if (origin == p && is_bang) {
                origin->m_game->draw_card_to(card_pile_type::player_hand, p);
            }
        });
    }

    void effect_red_ringo::on_equip(player *p, card *target_card) {
        p->m_game->add_event<event_type::on_game_start>(target_card, [p] {
            p->add_cubes(p->m_characters.front(), 4);
        });
    }

    bool effect_red_ringo::can_play(card *origin_card, player *origin, player *target, card *target_card) const {
        return origin->m_characters.front()->cubes.size() > 0
            && target_card->cubes.size() < 4;
    }

    void effect_red_ringo::on_play(card *origin_card, player *origin, player *target, card *target_card) {
        origin->move_cubes(origin->m_characters.front(), target_card, 1);
    }

    bool effect_ms_abigail::can_escape(const player *origin, card *target_card, effect_flags flags) const {
        if (!bool(flags & effect_flags::single_target)) return false;
        if (target_card->color != card_color_type::brown) return false;
        switch (target_card->value) {
        case card_value_type::value_J:
        case card_value_type::value_Q:
        case card_value_type::value_K:
        case card_value_type::value_A:
            return true;
        default:
            return false;
        }
    }

    bool effect_ms_abigail::can_respond(card *origin_card, player *origin) const {
        return can_escape(origin, origin->m_game->top_request().origin_card(), origin->m_game->top_request().flags());
    }

    void effect_ms_abigail::on_play(card *origin_card, player *origin) {
        origin->m_game->pop_request();
    }
}