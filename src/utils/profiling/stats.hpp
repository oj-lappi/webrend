#ifndef WEBREND_UTILS_STATS_HPP
#define WEBREND_UTILS_STATS_HPP

#include <nlohmann/json.hpp>
#include <vector>

#ifdef WEBREND_PROFILE
#    include "./hires_timer.hpp"
#endif
//#include <boost/histogram>

namespace webrend_profiling {

struct Distribution {
    double              bin_width;
    std::vector<size_t> bins;
} __attribute__((aligned(32)));

using integer_profile = std::vector<std::uint64_t>;

struct Profiler {
    std::map<std::string, integer_profile>     profiles;
    std::map<std::string, std::vector<size_t>> path_properties;
    std::string                                output_filename;
    Profiler(std::string output_filename);
    ~Profiler();
    void dump() const;
};

#ifdef WEBREND_PROFILE
extern Profiler stats;

#    define WEBREND_FUNC_PROFILE_BEGIN                                                                                 \
        auto                 &func_stats = webrend_profiling::stats.profiles[__func__];                                \
        high_resolution_timer timer;

#    define WEBREND_FUNC_PROFILE_END func_stats.push_back(timer.elapsed_nanoseconds());
#else
#    define WEBREND_FUNC_PROFILE_BEGIN ;
#    define WEBREND_FUNC_PROFILE_END   ;
#endif
} // namespace webrend_profiling

#endif
