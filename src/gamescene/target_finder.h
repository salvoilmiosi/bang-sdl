#ifndef __TARGET_FINDER_H__
#define __TARGET_FINDER_H__

#include "player.h"

#include "cards/holders.h"

#include <vector>

namespace banggame {

    class game_scene;

    enum class target_mode {
        start,
        modifier,
        target,
        equip,
        finish
    };

    struct target_status {
        card_view *m_playing_card = nullptr;
        card_view *m_picked_card = nullptr;
        target_list m_targets;
        modifier_list m_modifiers;
        effect_context m_context;
        std::vector<game_style_tracker> m_target_borders;
        std::vector<game_style_tracker> m_targetable_borders;
        target_mode m_mode = target_mode::start;

        card_view *get_current_card() const;
        target_list &get_current_target_list();
        const target_list &get_current_target_list() const;
    };

    struct request_status {
        card_modifier_tree m_play_cards;
        player_distances m_distances;
        std::optional<timer_status_args> m_request_timer;
        target_list m_request_target_set;
        std::vector<card_view *> m_pick_cards;
        std::vector<game_style_tracker> m_highlights;
        std::vector<game_style_tracker> m_request_borders;
        card_view *m_request_origin_card = nullptr;
        player_view *m_request_origin = nullptr;
        player_view *m_request_target = nullptr;
        bool m_response = false;

        std::optional<timer_id_t> get_timer_id() const {
            if (m_request_timer) return m_request_timer->timer_id;
            return std::nullopt;
        }
    };

    class target_finder : private target_status, private request_status {
    public:
        target_finder(game_scene *parent) : m_game(parent) {}

        bool is_card_clickable() const;
        bool can_confirm() const;
        
        int calc_distance(player_view *from, player_view *to) const;

        bool is_playing_card(card_view *card) const { return m_playing_card == card; }
        bool finished() const { return m_mode == target_mode::finish; }

        const request_status &get_request_status() const { return static_cast<const request_status &>(*this); }
    
    public:
        void set_response_cards(const request_status_args &args);
        void set_play_cards(const status_ready_args &args);
        
        void handle_auto_select();

        void clear_status();
        void clear_targets();

        void on_click_card(pocket_type pocket, player_view *player, card_view *card);
        bool on_click_player(player_view *player);
        
        void send_prompt_response(bool response);
    
    private:
        void set_request_borders();

        void select_playing_card(card_view *card);
        void select_equip_card(card_view *card);

        const card_modifier_tree &get_current_tree() const;
        bool can_play_card(card_view *card) const;
        bool finalize_last_target();

        void add_modifier_context(card_view *mod_card);

        bool can_pick_card(pocket_type pocket, player_view *player, card_view *card) const;

        struct player_target_check {
            const target_status &status;
            player_view *origin;
            target_player_filter filter;
            
            bool operator()(player_view *target_player) const;
        };

        struct card_target_check {
            const target_status &status;
            player_view *origin;
            target_card_filter filter;

            bool operator()(card_view *target_card) const;
        };

        int count_selected_cubes(card_view *card);
        bool add_selected_cube(card_view *card, int ncubes);

        void add_card_target(player_view *player, card_view *card);
        void handle_auto_targets();

        void send_pick_card(pocket_type pocket, player_view *player, card_view *card);
        void send_play_card();
        
        void send_game_action(const game_action &action);

        player_target_check make_target_check(target_player_filter filter) const;
        card_target_check make_target_check(target_card_filter filter) const;

    public:
        bool is_valid_target(target_player_filter filter, player_view *target_player) const {
            return make_target_check(filter)(target_player);
        }

        bool is_valid_target(target_card_filter filter, card_view *target_card) const {
            return make_target_check(filter)(target_card);
        }
        
    private:
        game_scene *m_game;
    };

}

#endif