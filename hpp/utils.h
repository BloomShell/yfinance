#pragma once
#include <algorithm>
#include <numeric>
#include <vector>
#include <string>
#include <array>
#include <unordered_map>
#include "../hpp/structures.h"
using time_point = std::chrono::time_point<std::chrono::high_resolution_clock>;


namespace Utils {

    namespace Types {
        typedef std::unordered_map<std::string,
            std::vector<Structures::Option>> Options;
    }

    namespace Statics {

        namespace Quotes {
            extern const std::string v8;
            extern std::unordered_map<std::string, int> ranges;
            extern std::array<std::string, 14> intervals;
        }

        namespace Options {
            extern const std::string v7;
        }

        namespace Overall {
            extern std::vector<std::string> nans;
        }
    }

    namespace Methods {
        std::string substring(
            const std::string& input,
            unsigned int start,
            unsigned int end
        );

        std::vector<int> findall(
            const std::vector<std::string>& v,
            const std::vector<std::string>& z
        );
    }

    namespace Benchmarking {
        template<typename Function, typename ... Args>
        Structures::TimeitResult Timeit(
            std::size_t iters, Function& f, Args&& ... args
        ) {
            if (iters < 1) throw std::runtime_error("Iters must be >= 1.");
            std::vector<std::chrono::milliseconds> durations;
            durations.reserve(iters);

            for (int it = 0; it < iters; it++) {
                time_point t0 = std::chrono::high_resolution_clock::now();
                f(std::forward<Args>(args)...);
                time_point t1 = std::chrono::high_resolution_clock::now();
                durations.emplace_back(
                    std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count());
            }

            milliseconds max = *std::max_element(durations.begin(), durations.end());
            milliseconds min = *std::min_element(durations.begin(), durations.end());
            milliseconds sum = std::accumulate(durations.begin(), durations.end(), milliseconds(0));
            milliseconds avg = sum / durations.size();

            return Structures::TimeitResult(iters, min, max, avg, sum);
        };
    }
}


inline std::ostream& operator<<(
    std::ostream& stream,
    const Utils::Types::Options& options)
{

    const unsigned int n_calls = options.at("calls").size();
    const unsigned int n_puts = options.at("puts").size();

    stream << "=======================================================================\n";
    stream << "============================= OPTIONS CONTENT =========================\n";
    stream << "=======================================================================\n\n";
    stream << "\tQueried info:\n";
    stream << "\t-----------------------------\n";
    stream << "\tCalls      \t: " << n_calls << "\n";
    stream << "\tPuts       \t: " << n_puts << "\n";
    stream << "\tExpiration \t: " << options.at("calls")[0].m_expiration.value() << "\n\n\n";
    return stream;

};
