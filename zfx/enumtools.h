#pragma once

#include <type_traits>
#include <utility>

namespace zeno {

template <class T, std::enable_if_t<std::is_enum_v<T>, int> = 0>
constexpr std::underlying_type_t<T> to_underlying(T t) noexcept {
    return static_cast<std::underlying_type_t<T>>(t);
}

template <class T, std::enable_if_t<!std::is_enum_v<T>, int> = 0>
constexpr T to_underlying(T t) noexcept {
    return t;
}

template <class To, class T>
constexpr To const &bit_cast(T const &t) noexcept {
    return *reinterpret_cast<To const *>(std::addressof(t));
}

template <class To, class T>
constexpr To &bit_cast(T &t) noexcept {
    return *reinterpret_cast<To *>(std::addressof(t));
}

}
