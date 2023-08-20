#pragma once
#include <functional>

namespace coro {
namespace detail {
template <typename T>
struct unwrap_reference {
  using type = T;
};

template <typename T>
struct unwrap_reference<std::reference_wrapper<T>> {
  using type = T;
};

template <typename T>
using unwrap_reference_t = typename unwrap_reference<T>::type;
}  // namespace detail
}  // namespace coro
