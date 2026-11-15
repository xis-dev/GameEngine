#pragma once
#include <iostream>
#include <format>

inline bool agp_assert_fail(const char* str, const char* fname, int line, const char* msg) {
    std::cerr <<
        std::format("AGP_ENGINE: Assertion failed: {}, {}:{}\n", str, fname, line)
     << msg << "\n";
    std::abort();
    return false;
}

// Assertions should only be
#ifdef DEBUG
#define AGPASSERT(cond, ...) \
    ((cond) || agp_assert_fail(#cond, __FILE__, __LINE__ \
    __VA_OPT__(,) __VA_ARGS__))

#else
#define AGPASSERT(cond, ...) (void(0))
#endif

