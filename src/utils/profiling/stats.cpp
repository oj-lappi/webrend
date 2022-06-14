#include "webrend.hpp"

#include <algorithm>
#include <boost/format.hpp>
#include <boost/histogram.hpp>
#include <map>
#include <vector>

#include "./stats.hpp"
#include "utils/file.hpp"
#include <fmt/format.h>

#include <nlohmann/json.hpp>

namespace webrend_profiling {

// json serialization of Distribution
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Distribution, bin_width, bins);

constexpr size_t BIN_WIDTH_NORMALIZED = 5;
constexpr size_t BIN_WIDTH_WALL_TIME  = 100;

Profiler::Profiler(std::string output_filename_) : output_filename(std::move(output_filename_)) {}

Profiler::~Profiler() { dump(); }

template <typename T>
std::map<std::string, Distribution>
make_distributions(std::map<std::string, std::vector<T>> sets, double bin_width, double trim)
{
    std::map<std::string, Distribution> distributions;
    for (const auto &[name, values] : sets) {
        using namespace boost::histogram;

        auto vals = values;
        sort(vals.begin(), vals.end());

        // Trim off the right tail
        size_t cutoff = (1.0f - trim) * vals.size();
        double max    = *(vals.begin() + (cutoff - 1));
        auto   end    = vals.begin() + cutoff;

        auto h = make_histogram_with(std::vector<size_t>(), axis::regular<>(axis::step(bin_width), 0, max));
        std::for_each(vals.begin(), end, std::ref(h));

        distributions.try_emplace(name, Distribution{bin_width, std::vector<size_t>(h.begin() + 1, h.end() - 1)});
    }
    return distributions;
}

void
Profiler::dump() const
{
    nlohmann::json   j{};
    constexpr double trim = 0.01;
    j["profiles"]         = make_distributions(profiles, BIN_WIDTH_WALL_TIME, 0.0);
    j["profiles_trimmed"] = make_distributions(profiles, BIN_WIDTH_WALL_TIME, trim);

    file_handle output_file{};

    std::string final_filename = fmt::format("{}.json", output_filename);
    fmt::print(" PROFILER: Writing performance profile to file \"{}\"\n", final_filename);
    output_file.open(final_filename, "wb");
    output_file.write(j.dump());
}

#ifdef WEBREND_PROFILE
Profiler stats("webrend_profile");
#endif

} // namespace webrend_profiling
