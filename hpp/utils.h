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

        namespace News {
            extern const std::string v11;
        }

        namespace Overall {
            extern std::vector<std::string> nans;
        }
    }
}
