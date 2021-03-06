#ifndef __INTL_H__
#define __INTL_H__

#include <string>
#include <ranges>
#include <fmt/format.h>
#include <fmt/args.h>

#include "locales/locales.h"

namespace intl {
    std::string translate(category cat, std::string_view str);

    std::string translate(category cat, enums::reflected_enum auto value) {
        return translate(cat, fmt::format("{}::{}", enums::enum_name_v<decltype(value)>, enums::to_string(value)));
    }

    template<typename ... Ts>
    std::string format(const std::string &format_str, const Ts & ... args) {
        try {
            return fmt::vformat(format_str, fmt::make_format_args(args ... ));
        } catch (const fmt::format_error &err) {
            return format_str;
        }
    }

    template<std::ranges::input_range R> requires std::convertible_to<std::ranges::range_value_t<R>, std::string>
    std::string format(const std::string &format_str, R &&args) {
        fmt::dynamic_format_arg_store<fmt::format_context> fmt_args;
        for (const std::string &arg : args) {
            fmt_args.push_back(arg);
        }

        try {
            return fmt::vformat(format_str, fmt_args);
        } catch (const fmt::format_error &err) {
            return format_str;
        }
    }
}

std::string _(intl::category cat, const auto &str) {
    return intl::translate(cat, str);
}

template<typename T, typename ... Ts>
std::string _(intl::category cat, const T &str, const Ts & ... args) {
    return intl::format(intl::translate(cat, str), args ...);
}

std::string _(const auto & ... args) {
    return _(intl::category::basic, args ...);
}

#endif