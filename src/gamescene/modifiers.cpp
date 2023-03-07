#include "target_finder.h"
#include "game.h"

#include "cards/effect_enums.h"
#include "cards/effect_context.h"
#include "cards/filters.h"

// TODO use server code

namespace banggame {

    bool target_finder::card_playable_with_modifier(card_view *mod_card, card_view *target_card) const {
        if (mod_card == target_card) {
            return false;
        } else if (target_card->is_modifier()) {
            switch (mod_card->modifier.type) {
            case modifier_type::bangmod:
            case modifier_type::doublebarrel:
            case modifier_type::bandolier:
                return target_card->modifier.type == modifier_type::bangmod
                    || target_card->modifier.type == modifier_type::doublebarrel
                    || target_card->modifier.type == modifier_type::bandolier;
            case modifier_type::discount:
                return target_card->deck == card_deck_type::goldrush && target_card->pocket->type != pocket_type::player_table;
            case modifier_type::card_choice:
            case modifier_type::leevankliff:
            case modifier_type::moneybag:
                return false;
            case modifier_type::locomotive:
                return target_card->pocket->type == pocket_type::stations;
            default:
                return true;
            }
        } else {
            switch (mod_card->modifier.type) {
            case modifier_type::bangmod:
            case modifier_type::doublebarrel:
            case modifier_type::bandolier:
                if (target_card->pocket->type == pocket_type::player_hand) {
                    return target_card->has_tag(tag_type::bangcard);
                } else {
                    return target_card->has_tag(tag_type::play_as_bang);
                }
            case modifier_type::discount:
                return target_card->deck == card_deck_type::goldrush && target_card->pocket->type != pocket_type::player_table;
            case modifier_type::card_choice:
                return mod_card->get_tag_value(tag_type::card_choice) == target_card->get_tag_value(tag_type::card_choice)
                    && !target_card->get_effect_list(m_response).empty();
            case modifier_type::belltower:
            case modifier_type::skip_player:
                return !filters::is_equip_card(target_card);
            case modifier_type::traincost:
            case modifier_type::locomotive:
                return target_card->pocket->type == pocket_type::train;
            default:
                return true;
            }
        }
    }

    void target_finder::add_modifier_context(card_view *mod_card) {
        switch (mod_card->modifier.type) {
        case modifier_type::belltower:
            m_context.ignore_distances = true;
            break;
        case modifier_type::card_choice:
            m_context.card_choice = mod_card;
            m_game->m_card_choice.set_anchor(mod_card, m_game->m_hidden_deck);
            break;
        case modifier_type::discount:
            m_context.discount = 1;
            break;
        case modifier_type::leevankliff:
            m_context.repeat_card = m_last_played_card;
            select_playing_card(m_context.repeat_card);
            break;
        case modifier_type::moneybag:
            m_context.repeat_card = m_game->m_discard_pile.back();
            select_playing_card(m_context.repeat_card);
            break;
        case modifier_type::traincost:
            m_context.traincost = mod_card;
            if (mod_card->pocket->type == pocket_type::stations) {
                size_t station_index = std::distance(m_game->m_stations.begin(), std::ranges::find(m_game->m_stations, m_context.traincost));
                size_t train_index = m_game->m_train_position - station_index + m_context.train_advance;
                select_equip_card(*(m_game->m_train.begin() + train_index));
            }
            break;
        case modifier_type::locomotive:
            m_context.train_advance = 1;
            break;
        }
    }

    void target_finder::add_modifier_context(card_view *mod_card, player_view *target) {
        switch (mod_card->modifier.type) {
        case modifier_type::skip_player:
            m_context.skipped_player = target;
            break;
        }
    }

    void target_finder::add_modifier_context(card_view *mod_card, card_view *target) {
        
    }

}