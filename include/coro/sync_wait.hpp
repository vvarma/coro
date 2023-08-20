#pragma once
#include <atomic>
#include <cstdint>

#include "coro/awaitable_traits.hpp"
#include "coro/detail/lightweight_manual_reset_event.hpp"
#include "coro/detail/sync_wait_task.hpp"

namespace coro {
template <typename AWAITABLE>
auto sync_wait(AWAITABLE&& awaitable) ->
    typename coro::awaitable_traits<AWAITABLE&&>::await_result_t {
  auto task = detail::make_sync_wait_task(std::forward<AWAITABLE>(awaitable));
  detail::lightweight_manual_reset_event event;
  task.start(event);
  event.wait();
  return task.result();
}
}  // namespace cppcoro
