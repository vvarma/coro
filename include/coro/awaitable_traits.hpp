#pragma once
#include "coro/detail/get_awaiter.hpp"

#include <type_traits>

namespace coro
{
	template<typename T, typename = void>
	struct awaitable_traits
	{};

	template<typename T>
	struct awaitable_traits<T, std::void_t<decltype(coro::detail::get_awaiter(std::declval<T>()))>>
	{
		using awaiter_t = decltype(coro::detail::get_awaiter(std::declval<T>()));

		using await_result_t = decltype(std::declval<awaiter_t>().await_resume());
	};
}

