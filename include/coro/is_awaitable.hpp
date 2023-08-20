#pragma once
#include "coro/detail/get_awaiter.hpp"

#include <type_traits>

namespace coro {
template <typename T, typename = std::void_t<>>
struct is_awaitable : std::false_type {};

template <typename T>
struct is_awaitable<
    T, std::void_t<decltype(coro::detail::get_awaiter(std::declval<T>()))>>
    : std::true_type {};

template <typename T> constexpr bool is_awaitable_v = is_awaitable<T>::value;
} // namespace coro
