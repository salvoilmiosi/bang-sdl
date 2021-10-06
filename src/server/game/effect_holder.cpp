#include "common/effect_holder.h"

#include <stdexcept>

namespace banggame {

    bool effect_holder::can_play(player *target) const {
        return enums::visit([=](auto tag, const auto &value) {
            if constexpr (requires { value.can_play(target); }) {
                return value.can_play(target);
            }
            return true;
        }, *this);
    }

    bool effect_holder::can_respond(player *target) const {
        return enums::visit([=](auto tag, const auto &value) {
            if constexpr (requires { value.can_respond(target); }) {
                return value.can_respond(target);
            }
            return false;
        }, *this);
    }

    void effect_holder::on_play(player *origin) {
        enums::visit([=](auto tag, auto &value) {
            if constexpr (requires { value.on_play(origin); }) {
                value.on_play(origin);
            } else {
                throw std::runtime_error("on_play(origin)");
            }
        }, *this);
    }

    void effect_holder::on_play(player *origin, player *target) {
        enums::visit([=](auto tag, auto &value) {
            if constexpr (requires { value.on_play(origin, target); }) {
                value.on_play(origin, target);
            } else {
                throw std::runtime_error("on_play(origin, target)");
            }
        }, *this);
    }

    void effect_holder::on_play(player *origin, player *target, int card_id) {
        enums::visit([=](auto tag, auto &value) {
            if constexpr (requires { value.on_play(origin, target, card_id); }) {
                value.on_play(origin, target, card_id);
            } else {
                throw std::runtime_error("on_play(origin, target, card_id)");
            }
        }, *this);
    }

    void equip_holder::on_equip(player *target, int card_id) {
        enums::visit([=](auto tag, auto &value) {
            value.on_equip(target, card_id);
        }, *this);
    }

    void equip_holder::on_unequip(player *target, int card_id) {
        enums::visit([=](auto tag, auto &value) {
            value.on_unequip(target, card_id);
        }, *this);
    }

    void equip_holder::on_predraw_check(player *target, int card_id) {
        enums::visit([=](auto tag, auto &value) {
            if constexpr (requires { value.on_predraw_check(target, card_id); }) {
                value.on_predraw_check(target, card_id);
            } else {
                throw std::runtime_error("on_predraw_check(target, card_id)");
            }
        }, *this);
    }

}