#pragma once

#include <atomic>
#include <cstdint>

namespace coro {
namespace detail {
class lightweight_manual_reset_event {
 public:
  lightweight_manual_reset_event(bool initiallySet = false);

  ~lightweight_manual_reset_event();

  void set() noexcept;

  void reset() noexcept;

  void wait() noexcept;

 private:
  std::atomic<int> m_value;
};
}  // namespace detail
}  // namespace coro
