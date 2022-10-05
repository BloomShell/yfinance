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

        namespace Summary {
            extern const std::string v11;
        }

        namespace Overall {
            extern std::vector<std::string> nans;
        }
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
