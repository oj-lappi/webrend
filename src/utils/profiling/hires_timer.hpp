#ifndef WEBREND_UTILS_HIRES_TIMER_HPP
#define WEBREND_UTILS_HIRES_TIMER_HPP
// High resolution timer borrowed from Bryce Adelstein-Lelbach's talk at, CppCon 2015, "Benchmarking C++ Code"
// Presentation: https://www.youtube.com/watch?v=zWxSZcpeS8Q
// Slides: https://github.com/CppCon/CppCon2015/tree/master/Presentations/Benchmarking%20C%2B%2B%20Code
// hi-res timer on page 52
#include <cstdint>

struct high_resolution_timer {
    std::uint64_t start_time;

    high_resolution_timer();
    void                 restart();
    double               elapsed() const;
    std::uint64_t        elapsed_nanoseconds() const;
    static std::uint64_t take_time_stamp();
};
#endif
