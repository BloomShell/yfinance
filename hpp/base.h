#include "boost/lexical_cast.hpp"
#include <nlohmann/json.hpp>
#include "../hpp/utils.h"
#include <cpr/cpr.h>
#include <algorithm>

namespace yfinance {

	namespace base {

		namespace quotes {

			yfinance::utils::constants::general::response get_quotes(
				const std::string&& symbol,
				const std::string&& interval,
				time_t&& start = -1,
				time_t&& end = -1
			);

			yfinance::utils::constants::quotes::qmap to_umap(
				yfinance::utils::constants::general::response& response
			);
		}
	}
}