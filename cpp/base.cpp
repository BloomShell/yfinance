#include "../hpp/utils.h"
#include "../hpp/base.h"

namespace yfinance {

	namespace base {

		namespace quotes {

			yfinance::utils::constants::general::response get_quotes(
				const std::string&& symbol,
				const std::string&& interval,
				time_t&& start,
				time_t&& end
			) {

				if (std::find(yfinance::utils::constants::quotes::intervals.begin(),
					yfinance::utils::constants::quotes::intervals.end(), interval) ==
					yfinance::utils::constants::quotes::intervals.end())
					throw std::invalid_argument("Invalid interval provided!");

				if (!((start != -1) && (end != -1))) {
					end = std::time(nullptr);
					if (yfinance::utils::constants::quotes::ranges.find(interval) ==
						yfinance::utils::constants::quotes::ranges.end()) start = 0;
					else start = (time_t)(end - (86400 *
						yfinance::utils::constants::quotes::ranges[interval]));
				}

				std::string period1 = boost::lexical_cast<std::string>(std::move(start));
				std::string period2 = boost::lexical_cast<std::string>(std::move(end));

				cpr::Response r = cpr::Get(cpr::Url{
					yfinance::utils::constants::quotes::v8 + symbol },
					cpr::Parameters{ {"interval", interval},
						{"period1", period1}, {"period2", period2} });

				if ((r.status_code == 200) && (!r.text.empty())) {
					return nlohmann::json::parse(r.text);
				}

			};

			yfinance::utils::constants::quotes::qmap to_umap(
				const yfinance::utils::constants::general::response& response
			) {
				yfinance::utils::constants::quotes::qmap umap;
				umap["unix"] = response["chart"]["result"][0]["timestamp"].dump();
				for (auto& col : { "open", "high", "low", "close", "volume" }) {
					umap[col] = response["chart"]["result"][0]["indicators"]["quote"][0][col].dump();
				}
				return umap;
			};

		}

	}

};