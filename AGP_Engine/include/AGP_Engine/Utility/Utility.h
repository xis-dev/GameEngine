#pragma once

#include <cstdlib>
#include <format>
#include <iostream>

template <typename... Args>
[[noreturn]] inline void agp_assert_fail(const char* expr, const char* file, int line,
                                         std::format_string<Args...> fmt, Args&&... args) {
    std::cerr << std::format("AGP_ENGINE: Assertion failed: {} at {}:{}\n  msg: {}\n",
                             expr, file, line,
                             std::format(fmt, std::forward<Args>(args)...));
    std::abort();
}

[[noreturn]] inline void agp_assert_fail(const char* expr, const char* file, int line) {
    std::cerr << std::format("AGP_ENGINE: Assertion failed: {} at {}:{}\n", expr, file, line);
    std::abort();
}

#ifndef NDEBUG
#define AGPASSERT(cond, ...) \
((cond) ? (void)0 : agp_assert_fail(#cond, __FILE__, __LINE__ __VA_OPT__(,) __VA_ARGS__))
#else
#define AGPASSERT(cond, ...) ((void)0)
#endif