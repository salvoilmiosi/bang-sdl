#include "common/effects/equips_valleyofshadows.h"

#include "../game.h"

namespace banggame {

    void effect_lemat::on_equip(player *p, card *origin_card) {
        p->add_player_flags(player_flags::treat_any_as_bang);
    }

    void effect_lemat::on_unequip(player *p, card *origin_card) {
        p->remove_player_flags(player_flags::treat_any_as_bang);
    }

    void effect_snake::on_equip(player *target, card *target_card) {
        target->add_predraw_check(target_card, 0, [=](card *drawn_card) {
            if (target->get_card_suit(drawn_card) == card_suit_type::spades) {
                target->damage(target_card, nullptr, 1);
            }
            target->next_predraw_check(target_card);
        });
    }

    void effect_ghost::on_pre_equip(player *target, card *target_card) {
        for (character *c : target->m_characters) {
            if (!target->m_game->is_disabled(c) && !target->alive()) {
                c->on_equip(target);
            }
        }
        target->m_game->add_event<event_type::post_discard_card>(target_card, [=](player *p, card *c) {
            if (p == target && c == target_card) {
                target->remove_player_flags(player_flags::ghost);
                target->m_game->player_death(nullptr, target);
                target->m_game->check_game_over(nullptr, target);
                target->m_game->remove_events(target_card);
            }
        });
    }

    void effect_ghost::on_equip(player *target, card *target_card) {
        target->m_game->add_public_update<game_update_type::player_hp>(target->id, 0, false);
        target->add_player_flags(player_flags::ghost);
    }

    void effect_ghost::on_unequip(player *target, card *target_card) {
        target->m_game->add_public_update<game_update_type::player_hp>(target->id, 0, true);
        target->remove_player_flags(player_flags::ghost);
    }

    void effect_shotgun::on_equip(player *p, card *target_card) {
        p->m_game->add_event<event_type::on_hit>(target_card, [=](card *origin_card, player *origin, player *target, int damage, bool is_bang) {
            if (origin == p && target != p && !target->m_hand.empty() && is_bang) {
                target->m_game->queue_request<request_type::discard>(target_card, origin, target);
            }
        });
    }

    void effect_bounty::on_equip(player *p, card *target_card) {
        p->m_game->add_event<event_type::on_hit>(target_card, [p](card *origin_card, player *origin, player *target, int damage, bool is_bang) {
            if (origin && target == p && is_bang) {
                origin->m_game->draw_card_to(card_pile_type::player_hand, origin);
            }
        });
    }
}