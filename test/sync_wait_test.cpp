
#include "coro/sync_wait.hpp"

#include <doctest/doctest.h>

#include <string>
#include <type_traits>

#include "coro/config.hpp"
#include "coro/on_scope_exit.hpp"
#include "coro/shared_task.hpp"
#include "coro/static_thread_pool.hpp"
#include "coro/task.hpp"

TEST_SUITE_BEGIN("sync_wait");

static_assert(std::is_same<decltype(coro::sync_wait(
                               std::declval<coro::task<std::string>>())),
                           std::string&&>::value);
static_assert(std::is_same<decltype(coro::sync_wait(
                               std::declval<coro::task<std::string>&>())),
                           std::string&>::value);

TEST_CASE("sync_wait(task<T>)") {
  auto makeTask = []() -> coro::task<std::string> { co_return "foo"; };

  auto task = makeTask();
  CHECK(coro::sync_wait(task) == "foo");

  CHECK(coro::sync_wait(makeTask()) == "foo");
}

TEST_CASE("sync_wait(shared_task<T>)") {
  auto makeTask = []() -> coro::shared_task<std::string> { co_return "foo"; };

  auto task = makeTask();

  CHECK(coro::sync_wait(task) == "foo");
  CHECK(coro::sync_wait(makeTask()) == "foo");
}

TEST_CASE("multiple threads") {
  // We are creating a new task and starting it inside the sync_wait().
  // The task will reschedule itself for resumption on a thread-pool thread
  // which will sometimes complete before this thread calls event.wait()
  // inside sync_wait(). Thus we're roughly testing the thread-safety of
  // sync_wait().
  coro::static_thread_pool tp{1};

  int value = 0;
  auto createLazyTask = [&]() -> coro::task<int> {
    co_await tp.schedule();
    co_return value++;
  };

  for (int i = 0; i < 10'000; ++i) {
    CHECK(coro::sync_wait(createLazyTask()) == i);
  }
}

TEST_SUITE_END();
