#ifndef __TARGET_FINDER_H__
#define __TARGET_FINDER_H__

#include "player.h"

#include "game/holders.h"
#include "utils/nullable.h"

#include <vector>

namespace banggame {

    class game_scene;

    template<target_type E> struct client_target_transform {
        using type = void;
    };

    template<> struct client_target_transform<target_type::player> {
        using type = player_view *;
    };

    template<> struct client_target_transform<target_type::conditional_player> {
        using type = nullable<player_view>;
    };

    struct target_card {
        player_view *player;
        card_view *card;
        bool operator == (const target_card &) const = default;
    };

    template<> struct client_target_transform<target_type::card> {
        using type = target_card;
    };

    template<> struct client_target_transform<target_type::cards_other_players> {
        using type = std::vector<target_card>;
    };

    struct target_cube {
        card_view *card;
        cube_widget *cube;
        bool operator == (const target_cube &) const = default;
    };

    template<> struct client_target_transform<target_type::cube> {
        using type = std::vector<target_cube>;
    };

    using target_variant_base = enums::enum_variant<target_type, client_target_transform>;
    
    struct target_variant {
        target_variant_base value{enums::enum_tag<target_type::none>};
        bool autotarget = false;
    };
    using target_vector = std::vector<target_variant>;

    struct target_status {
        card_view *m_playing_card = nullptr;
        std::vector<card_view *> m_modifiers;

        target_vector m_targets;

        bool m_equipping = false;
        bool m_response = false;
    };

    class target_finder : private target_status {
    public:
        target_finder(game_scene *parent) : m_game(parent) {}
        
        void set_border_colors();

        bool can_respond_with(card_view *card) const;
        bool can_play_in_turn(player_view *player, card_view *card) const;
        bool can_confirm() const;

        void set_response_highlights(const request_status_args &args);
        void clear_status();
        void clear_targets();

        void set_last_played_card(card_view *card) {
            m_last_played_card = card;
        }

        void set_forced_card(card_view *card);

        void confirm_play(bool valid);
        bool waiting_confirm() const {
            return m_waiting_confirm;
        }

        bool is_card_clickable() const;

        void on_click_discard_pile();
        void on_click_main_deck();
        void on_click_selection_card(card_view *card);
        void on_click_shop_card(card_view *card);
        void on_click_table_card(player_view *player, card_view *card);
        void on_click_hand_card(player_view *player, card_view *card);
        void on_click_character(player_view *player, card_view *card);
        void on_click_scenario_card(card_view *card);
        bool on_click_player(player_view *player);

        void on_click_confirm();

        bool is_playing_card(card_view *card) const {
            return m_playing_card == card;
        }
        
        void send_prompt_response(bool response);
    
    private:
        bool is_bangcard(card_view *card);

        void add_modifier(card_view *card);
        bool verify_modifier(card_view *card);

        void handle_auto_targets();

        std::optional<std::string> verify_player_target(target_player_filter filter, player_view *target_player);
        std::optional<std::string> verify_card_target(const effect_holder &args, target_card target);

        void add_card_target(target_card target);
        
        int calc_distance(player_view *from, player_view *to);

        const card_view *get_current_card() const;
        const effect_list &get_current_card_effects() const;

        bool send_pick_card(pocket_type pocket, player_view *player = nullptr, card_view *card = nullptr);
        void send_play_card();

        const effect_holder &get_effect_holder(int index);
        int num_targets_for(const effect_holder &data);
        int count_selected_cubes(card_view *card);
        std::vector<player_view *> possible_player_targets(target_player_filter filter);
        int get_target_index();
        
    private:
        game_scene *m_game;

        std::vector<card_view *> m_response_highlights;
        std::vector<std::tuple<pocket_type, player_view *, card_view *>> m_picking_highlights;

        card_view *m_last_played_card = nullptr;
        card_view *m_forced_card = nullptr;
        bool m_waiting_confirm = false;

        template<game_action_type T, typename ... Ts>
        void add_action(Ts && ... args);
    };

}

#endif