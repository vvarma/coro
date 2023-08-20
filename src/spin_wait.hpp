#pragma once
#include <cstdint>

namespace coro {
class spin_wait {
 public:
  spin_wait() noexcept;

  bool next_spin_will_yield() const noexcept;

  void spin_one() noexcept;

  void reset() noexcept;

 private:
  std::uint32_t m_count;
};
}  // namespace coro
