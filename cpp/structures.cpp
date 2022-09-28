#include "..\hpp\structures.h"
#include "..\hpp\base.h"
#include "..\hpp\utils.h"
#include <iostream>

namespace yfinance {

	namespace structures {

		namespace quotes {

			void Quote::load(
				const yfinance::utils::constants::general::response& response,
				const std::string&& sep
			) {
				yfinance::utils::constants::quotes::qmap qmap = yfinance::base::quotes::to_umap(response);

				// Read json' string to vector of strings through boost-split:
				std::unordered_map<std::string, std::vector<std::string>> map;

				for (auto& col : { "open", "high", "low", "close", "volume", "unix" }) {
					boost::split(map[col], yfinance::utils::methods::substring(
						qmap[col], 1, 2), boost::is_any_of(sep));
				}

				std::vector<int> indexes = yfinance::utils::methods::findall(map["close"],
					yfinance::utils::constants::general::NaNs);
				std::sort(indexes.rbegin(), indexes.rend());
				for (auto& col : { "open", "high", "low", "close", "volume", "unix" }) {
					for (auto& index : indexes) map[col].erase(map[col].begin() + index);
				}

				unsigned int size = map["unix"].size();
				std::vector<float> open(size), high(size), low(size), close(size);
				std::vector<long int> volume(size);
				std::vector<time_t> unix(size);

				std::transform(map["open"].begin(), map["open"].end(), open.begin(),
					[](const std::string& token) { return std::stof(token); });
				std::transform(map["high"].begin(), map["high"].end(), high.begin(),
					[](const std::string& token) { return std::stof(token); });
				std::transform(map["low"].begin(), map["low"].end(), low.begin(),
					[](const std::string& token) { return std::stof(token); });
				std::transform(map["close"].begin(), map["close"].end(), close.begin(),
					[](const std::string& token) { return std::stof(token); });
				std::transform(map["volume"].begin(), map["volume"].end(), volume.begin(),
					[](const std::string& token) { return std::stoll(token); });
				std::transform(map["unix"].begin(), map["unix"].end(), unix.begin(),
					[](const std::string& token) { return (time_t)std::stoll(token); });

				this->base.m_open = open;
				this->base.m_high = high;
				this->base.m_low = low;
				this->base.m_close = close;
				this->base.m_volume = volume;
				this->base.m_unix = unix;
				this->m_empty = false;
			}
			
			void Quote::summary() {
					
					if (this->m_empty) {
						throw std::length_error("Empty Quote.");
					}
					else {

						unsigned int size = this->base.m_close.size();
						std::cout << "=======================================================================\n";
						std::cout << "============================== QUOTE CONTENT ==========================\n";
						std::cout << "=======================================================================\n\n";
						std::cout << "\tQueried info:\n";
						std::cout << "\t----------------------------\n";
						std::cout << "\tSymbol         \t: " << this->m_symbol << "\n";
						std::cout << "\tObservations   \t: " << size << "\n";
						std::cout << "\tStarting (Unix)\t: " << this->base.m_unix[0] << "\n";
						std::cout << "\tEnding (Unix)  \t: " << this->base.m_unix[size - 1] << "\n\n\n";
					}
				}
			
		}
	}
}