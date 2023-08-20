
#pragma once
#include <condition_variable>
#include <mutex>

#include "coro/config.hpp"

namespace coro {
class auto_reset_event {
 public:
  auto_reset_event(bool initiallySet = false);

  ~auto_reset_event();

  void set();

  void wait();

 private:
  std::mutex m_mutex;
  std::condition_variable m_cv;
  bool m_isSet;
};
}  // namespace cppcoro
