#pragma once
#include "coro/detail/any.hpp"
#include "coro/detail/is_awaiter.hpp"

namespace coro {
namespace detail {
template <typename T>
auto get_awaiter_impl(T &&value, int) noexcept(
    noexcept(static_cast<T &&>(value).operator co_await()))
    -> decltype(static_cast<T &&>(value).operator co_await()) {
  return static_cast<T &&>(value).operator co_await();
}

template <typename T>
auto get_awaiter_impl(T &&value, long) noexcept(
    noexcept(operator co_await(static_cast<T &&>(value))))
    -> decltype(operator co_await(static_cast<T &&>(value))) {
  return operator co_await(static_cast<T &&>(value));
}

template <typename T,
          std::enable_if_t<coro::detail::is_awaiter<T &&>::value, int> = 0>
T &&get_awaiter_impl(T &&value, coro::detail::any) noexcept {
  return static_cast<T &&>(value);
}

template <typename T>
auto get_awaiter(T &&value) noexcept(
    noexcept(detail::get_awaiter_impl(static_cast<T &&>(value), 123)))
    -> decltype(detail::get_awaiter_impl(static_cast<T &&>(value), 123)) {
  return detail::get_awaiter_impl(static_cast<T &&>(value), 123);
}
} // namespace detail
} // namespace coro
