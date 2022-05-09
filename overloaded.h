#pragma once

#include <variant>
#include <utility>

template <class ...Fs>
struct overloaded : Fs... {
    using Fs::operator()...;

    template <class ...Ts>
    decltype(auto) match(Ts &&...ts) const {
        return std::visit(*this, std::forward<Ts>(ts)...);
    }
};

template <class ...Fs>
overloaded(Fs...) -> overloaded<Fs...>;

