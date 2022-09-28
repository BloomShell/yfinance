#pragma once
#include <vector>
#include <array>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <nlohmann/json.hpp>

namespace yfinance {

	namespace utils {

		namespace methods {

			std::string substring(
				const std::string& input,
				unsigned int start,
				unsigned int end
			);

			std::vector<int> findall(
				const std::vector<std::string>& v,
				const std::vector<std::string> z
			);

		}

		namespace constants {

			namespace quotes {

				extern std::unordered_map<std::string, int> ranges;
				extern const std::string v8;
				typedef std::unordered_map<std::string, std::string> qmap;
				extern std::array<std::string, 14> intervals;
			}

			namespace general {

				extern std::vector<std::string> NaNs;
				typedef nlohmann::json response;
			}
		}
	}
}