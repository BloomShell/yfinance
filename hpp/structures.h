#pragma once
#include <boost/algorithm/string.hpp>
#include <algorithm>
#include <vector>
#include <string>
#include "utils.h"

namespace yfinance {

	namespace structures {

		namespace quotes {

			struct Base {

				std::vector<float> m_open, m_high, m_low, m_close;
				std::vector<long int> m_volume;
				std::vector<time_t> m_unix;

				Base() = default;

				Base(
					std::vector<float> open, std::vector<float> high,
					std::vector<float> low, std::vector<float> close,
					std::vector<long int> volume, std::vector<time_t> unix
				)
					: m_open(open), m_high(high), m_low(low), m_close(close),
					m_volume(volume), m_unix(unix) {}

			};

			class Quote {
				
				public:

					bool m_empty = true;
					std::string m_symbol;
					Base base;

					Quote(std::string symbol) 
						: m_symbol(symbol) {};
						
					void load(
						const yfinance::utils::constants::general::response& response,
						const std::string&& sep
					);

					void summary();

				};
		}
	}
}