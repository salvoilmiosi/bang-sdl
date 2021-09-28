#include "player.h"

#include "game.h"

#include "common/effects.h"
#include "common/responses.h"
#include "common/net_enums.h"

namespace banggame {
    constexpr auto is_weapon = [](const card &c) {
        return !c.effects.empty() && c.effects.front().is<effect_weapon>();
    };

    void player::discard_weapon() {
        auto it = std::ranges::find_if(m_table, is_weapon);
        if (it != m_table.end()) {
            auto &moved = get_game()->add_to_discards(std::move(*it));
            for (auto &e : moved.effects) {
                e->on_unequip(this, &moved);
            }
            m_table.erase(it);
        }
    }

    void player::equip_card(card &&target) {
        for (auto &e : target.effects) {
            e->on_equip(this, &target);
        }
        auto &moved = m_table.emplace_back(std::move(target));
        get_game()->add_show_card(moved);
        get_game()->add_public_update<game_update_type::move_card>(moved.id, card_pile_type::player_table, id);
    }

    bool player::has_card_equipped(const std::string &name) const {
        return std::ranges::find(m_table, name, &card::name) != m_table.end();
    }

    card player::get_card_removed(card *target) {
        auto it = std::ranges::find(m_table, target->id, &card::id);
        card c;
        if (it == m_table.end()) {
            it = std::ranges::find(m_hand, target->id, &card::id);
            c = std::move(*it);
            m_hand.erase(it);
        } else {
            if (auto inactive_it = std::ranges::find(m_inactive_cards, it->id); inactive_it != m_inactive_cards.end()) {
                m_inactive_cards.erase(inactive_it);
            }
            c = std::move(*it);
            for (auto &e : c.effects) {
                e->on_unequip(this, &c);
            }
            m_table.erase(it);
        }
        return c;
    }

    card &player::discard_card(card *target) {
        return get_game()->add_to_discards(get_card_removed(target));
    }

    void player::steal_card(player *target, card *target_card) {
        const card &c = m_hand.emplace_back(target->get_card_removed(target_card));
        get_game()->add_show_card(c, this);
        get_game()->add_public_update<game_update_type::move_card>(c.id, card_pile_type::player_hand, id);
    }

    void player::damage(int value) {
        m_hp -= value;
        get_game()->add_public_update<game_update_type::player_hp>(id, m_hp);
        if (m_hp <= 0) {
            get_game()->add_response<response_type::death>(nullptr, this);
        }
    }

    void player::heal(int value) {
        m_hp = std::min(m_hp + value, m_max_hp);
        get_game()->add_public_update<game_update_type::player_hp>(id, m_hp);
    }

    void player::add_to_hand(card &&target) {
        const auto &c = m_hand.emplace_back(std::move(target));
        get_game()->add_show_card(c, this);
        get_game()->add_public_update<game_update_type::move_card>(c.id, card_pile_type::player_hand, id);
    }

    bool player::verify_card_targets(const card &c, const std::vector<play_card_target> &targets) {
        auto in_range = [this](int player_id, int distance) {
            return distance == 0 || get_game()->calc_distance(this, get_game()->get_player(player_id)) <= distance;
        };
        if (c.color == card_color_type::blue) {
            if (c.effects.empty() || targets.size() != 1) return false;
            if (targets.front().enum_index() != play_card_target_type::target_player) return false;
            const auto &tgts = targets.front().get<play_card_target_type::target_player>();
            if (tgts.size() != 1) return false;
            switch (c.effects.front()->target) {
            case target_type::none:
            case target_type::self:
                return tgts.front().player_id == id;
            case target_type::notself:
                return tgts.front().player_id != id && in_range(tgts.front().player_id, c.effects.front()->maxdistance);
            case target_type::notsheriff:
                return get_game()->get_player(tgts.front().player_id)->role() != player_role::sheriff
                    && in_range(tgts.front().player_id, c.effects.front()->maxdistance);
            case target_type::reachable:
                return in_range(tgts.front().player_id, m_weapon_range);
            default:
                return false;
            }
        }
        if (c.effects.size() != targets.size()) return false;
        return std::ranges::all_of(c.effects, [&, it = targets.begin()] (const effect_holder &e) mutable {
            return enums::visit(util::overloaded{
                [&](enums::enum_constant<play_card_target_type::target_none>) {
                    return e->target == target_type::none || e->target == target_type::response;
                },
                [&](enums::enum_constant<play_card_target_type::target_player>, const std::vector<target_player_id> &args) {
                    switch (e->target) {
                    case target_type::self:
                        return args.size() == 1 && args.front().player_id == id;
                    case target_type::notself:
                        return args.size() == 1 && args.front().player_id != id
                            && in_range(args.front().player_id, e->maxdistance);
                    case target_type::everyone:
                        if (args.size() != get_game()->m_players.size()) return false;
                        return std::ranges::all_of(get_game()->m_players, [&](int pid) {
                            return std::ranges::find(args, pid, &target_player_id::player_id) != args.end();
                        }, &player::id);
                    case target_type::others:
                        if (args.size() != get_game()->m_players.size() - 1) return false;
                        return std::ranges::all_of(get_game()->m_players, [&](int pid) {
                            auto it = std::ranges::find(args, pid, &target_player_id::player_id);
                            return (id == pid) != (it == args.end());
                        }, &player::id);
                    case target_type::notsheriff:
                        return args.size() == 1 && get_game()->get_player(args.front().player_id)->role() != player_role::sheriff
                            && in_range(args.front().player_id, c.effects.front()->maxdistance);
                    case target_type::reachable:
                        return args.size() == 1 && in_range(args.front().player_id, m_weapon_range);
                    default:
                        return false;
                    }
                },
                [&](enums::enum_constant<play_card_target_type::target_card>, const std::vector<target_card_id> &args) {
                    switch (e->target) {
                    case target_type::selfhand:
                        return args.size() == 1 && args.front().player_id == id && m_hand.at(args.front().card_index).id != c.id;
                    case target_type::othercards:
                        if (args.size() != get_game()->m_players.size() - 1) return false;
                        return std::ranges::all_of(get_game()->m_players, [&](int pid) {
                            auto it = std::ranges::find(args, pid, &target_card_id::player_id);
                            return (id == pid) != (it == args.end());
                        }, &player::id);
                    case target_type::anycard:
                        if (args.size() != 1) return false;
                        if (!in_range(args.front().player_id, e->maxdistance)) return false;
                        if (args.front().player_id == id && args.front().from_hand
                            && m_hand.at(args.front().card_index).id == c.id) return false;
                        return true;
                    default:
                        return false;
                    }
                }
            }, *it++);
        });
    }

    void player::do_play_card(card &c, const std::vector<play_card_target> &targets) {
        auto effect_it = targets.begin();
        for (auto &e : c.effects) {
            enums::visit(util::overloaded{
                [&](enums::enum_constant<play_card_target_type::target_none>) {
                    e->on_play(this);
                },
                [&](enums::enum_constant<play_card_target_type::target_player>, const std::vector<target_player_id> &args) {
                    for (const auto &target : args) {
                        e->on_play(this, get_game()->get_player(target.player_id));
                    }
                },
                [&](enums::enum_constant<play_card_target_type::target_card>, const std::vector<target_card_id> &args) {
                    for (const auto &target : args) {
                        auto *target_player = get_game()->get_player(target.player_id);
                        card *target_card = nullptr;
                        if (target.from_hand) {
                            if (target_player == this) {
                                target_card = &m_hand.at(target.card_index);
                            } else {
                                target_card = &target_player->m_hand.at(get_game()->rng() % target_player->m_hand.size());
                            }
                        } else {
                            target_card = &target_player->m_table.at(target.card_index);
                        }
                        e->on_play(this, target_player, target_card);
                    }
                }
            }, *effect_it++);
        }
    }

    void player::play_card(const play_card_args &args) {
        auto card_it = std::ranges::find(m_hand, args.card_id, &card::id);
        if (card_it == m_hand.end()) {
            card_it = std::ranges::find(m_table, args.card_id, &card::id);
            switch (card_it->color) {
            case card_color_type::green:
                if (std::ranges::find(m_inactive_cards, card_it->id) == m_inactive_cards.end()) {
                    if (verify_card_targets(*card_it, args.targets)) {
                        card removed = std::move(*card_it);
                        m_hand.erase(card_it);
                        do_play_card(removed, args.targets);
                        get_game()->add_to_discards(std::move(removed));
                    } else {
                        throw error_message("Target non validi");
                    }
                }
                break;
            default:
                throw error_message("Carta giocata non valida");
            }
        } else {
            switch (card_it->color) {
            case card_color_type::brown:
                if (verify_card_targets(*card_it, args.targets)) {
                    card removed = std::move(*card_it);
                    do_play_card(removed, args.targets);
                    get_game()->add_to_discards(std::move(removed));
                } else {
                    throw error_message("Target non validi");
                }
                break;
            case card_color_type::blue:
                if (verify_card_targets(*card_it, args.targets)) {
                    auto *target_player = get_game()->get_player(
                        args.targets.front().get<play_card_target_type::target_player>().front().player_id);
                    if (!target_player->has_card_equipped(card_it->name)) {
                        card removed = std::move(*card_it);
                        m_hand.erase(card_it);
                        target_player->equip_card(std::move(removed));
                    }
                } else {
                    throw error_message("Target non validi");
                }
                break;
            case card_color_type::green:
                if (!has_card_equipped(card_it->name)) {
                    card removed = std::move(*card_it);
                    int card_id = m_inactive_cards.emplace_back(removed.id);
                    m_hand.erase(card_it);
                    equip_card(std::move(removed));
                    get_game()->add_public_update<game_update_type::tap_card>(card_id, false);
                }
                break;
            }
        }
    }
    
    void player::respond_card(const play_card_args &args) {
        auto *resp = get_game()->top_response().as<card_response>();
        if (!resp) return;

        auto card_it = std::ranges::find(m_hand, args.card_id, &card::id);
        if (card_it == m_hand.end()) {
            switch (card_it->color) {
            case card_color_type::green:
                if (std::ranges::find(m_inactive_cards, card_it->id) == m_inactive_cards.end()) {
                    if (verify_card_targets(*card_it, args.targets)) {
                        if (resp->on_respond(&*card_it)) {
                            card removed = std::move(*card_it);
                            m_table.erase(card_it);
                            do_play_card(removed, args.targets);
                            get_game()->add_to_discards(std::move(removed));
                        }
                    } else {
                        throw error_message("Target non validi");
                    }
                }
                break;
            case card_color_type::blue:
                resp->on_respond(&*card_it);
            default:
                throw error_message("Carta giocata non valida");
            }
        } else {
            card_it = std::ranges::find(m_table, args.card_id, &card::id);
            if (card_it != m_table.end() && card_it->color == card_color_type::brown) {
                if (verify_card_targets(*card_it, args.targets)) {
                    if (resp->on_respond(&*card_it)) {
                        card removed = std::move(*card_it);
                        m_hand.erase(card_it);
                        do_play_card(removed, args.targets);
                        get_game()->add_to_discards(std::move(removed));
                    }
                } else {
                    throw error_message("Target non validi");
                }
            }
        }
    }

    void player::start_of_turn() {
        get_game()->add_public_update<game_update_type::switch_turn>(id);

        m_pending_predraw_checks = m_predraw_checks;

        if (m_pending_predraw_checks.empty()) {
            get_game()->queue_response<response_type::draw>(nullptr, this);
        } else {
            get_game()->queue_response<response_type::predraw>(nullptr, this);
        }
    }

    void player::next_predraw_check(int card_id) {
        m_pending_predraw_checks.erase(std::ranges::find(m_pending_predraw_checks, card_id, &predraw_check_t::card_id));

        if (m_pending_predraw_checks.empty()) {
            get_game()->queue_response<response_type::draw>(nullptr, this);
        } else {
            get_game()->queue_response<response_type::predraw>(nullptr, this);
        }
    }

    void player::end_of_turn() {
        for (int id : m_inactive_cards) {
            get_game()->add_public_update<game_update_type::tap_card>(id, true);
        }
        m_inactive_cards.clear();
        m_pending_predraw_checks.clear();
    }

    void player::discard_all() {
        for (card &c : m_table) {
            get_game()->add_to_discards(std::move(c));
        }
        for (card &c : m_hand) {
            get_game()->add_to_discards(std::move(c));
        }
    }

    void player::set_character_and_role(const character &c, player_role role) {
        m_character = c;
        m_role = role;

        m_max_hp = c.max_hp;

        m_character.effect->on_equip(this, nullptr);
        get_game()->add_public_update<game_update_type::player_character>(id, c.id, c.name, c.image, c.effect->target);

        if (role == player_role::sheriff) {
            ++m_max_hp;
            get_game()->add_public_update<game_update_type::player_show_role>(id, m_role);
        } else {
            get_game()->add_private_update<game_update_type::player_show_role>(this, id, m_role);
        }

        m_hp = m_max_hp;
        get_game()->add_public_update<game_update_type::player_hp>(id, m_hp);
    }
}