#pragma once
namespace coro {
namespace detail {
// Helper type that can be cast-to from any type.
struct any {
  template <typename T> any(T &&) noexcept {}
};
} // namespace detail
} // namespace cppcoro
