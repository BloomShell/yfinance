#include "../hpp/base.h"
#include "../hpp/utils.h"

namespace yfinance {

	Structures::Quotes Symbol::get_quotes(
		const std::string&& interval,
		time_t&& start,
		time_t&& end,
		const std::string sep
	) {
		if (std::find(
			Utils::Statics::Quotes::intervals.begin(),
			Utils::Statics::Quotes::intervals.end(),
			interval) == Utils::Statics::Quotes::intervals.end())
			throw std::invalid_argument("Invalid interval provided!");

		if (!((start != -1) && (end != -1))) {
			end = std::time(nullptr);
			if (Utils::Statics::Quotes::ranges.find(interval) ==
				Utils::Statics::Quotes::ranges.end()) start = 0;
			else start = (time_t)(end - (86400 *
				Utils::Statics::Quotes::ranges[interval]));
		}

		std::string period1 = boost::lexical_cast<std::string>(std::move(start));
		std::string period2 = boost::lexical_cast<std::string>(std::move(end));

		cpr::Response r = cpr::Get(cpr::Url{
			Utils::Statics::Quotes::v8 + m_symbol },
			cpr::Parameters{ {"interval", interval},
				{"period1", period1}, {"period2", period2} });

		if ((r.status_code == 200) && (!r.text.empty())) {
			json rjson = nlohmann::json::parse(r.text);

			// Read json' string to vector of strings through boost-split:
			std::unordered_map<std::string, std::vector<std::string>> quotemap;
			boost::split(quotemap["unix"], Utils::Methods::substring(
				rjson["chart"]["result"][0]["timestamp"].dump(), 1, 2),
				boost::is_any_of(sep));
			for (auto& col : { "open", "high", "low", "close", "volume" }) {
				boost::split(quotemap[col], Utils::Methods::substring(
					rjson["chart"]["result"][0]["indicators"]
					["quote"][0][col].dump(), 1, 2), boost::is_any_of(sep));
			}

			// Deleting NaNs:
			std::vector<int> indexes = Utils::Methods::findall(quotemap["close"],
				Utils::Statics::Overall::nans);
			std::sort(indexes.rbegin(), indexes.rend());
			for (auto& col : { "open", "high", "low", "close", "volume", "unix" }) {
				for (auto& index : indexes) quotemap[col].erase(
					quotemap[col].begin() + index);
			}

			unsigned int size = quotemap["unix"].size();
			std::vector<float> open(size), high(size), low(size), close(size);
			std::vector<long int> volume(size);
			std::vector<time_t> unix(size);

			std::transform(quotemap["open"].begin(), quotemap["open"].end(), open.begin(),
				[](const std::string& token) { return std::stof(token); });
			std::transform(quotemap["high"].begin(), quotemap["high"].end(), high.begin(),
				[](const std::string& token) { return std::stof(token); });
			std::transform(quotemap["low"].begin(), quotemap["low"].end(), low.begin(),
				[](const std::string& token) { return std::stof(token); });
			std::transform(quotemap["close"].begin(), quotemap["close"].end(), close.begin(),
				[](const std::string& token) { return std::stof(token); });
			std::transform(quotemap["volume"].begin(), quotemap["volume"].end(), volume.begin(),
				[](const std::string& token) { return std::stoll(token); });
			std::transform(quotemap["unix"].begin(), quotemap["unix"].end(), unix.begin(),
				[](const std::string& token) { return (time_t)std::stoll(token); });

			return Structures::Quotes(
				std::move(open),
				std::move(high),
				std::move(low),
				std::move(close),
				std::move(volume),
				std::move(unix)
			);
		}
		else {
			std::string error_message =
				"Request failed with status code: " + r.status_code;
			throw std::runtime_error(error_message);
		}
	}

	Utils::Types::Options Symbol::get_options(

	) {
		Utils::Types::Options options;
		std::vector<Structures::Option> calls, puts;
		options["CALL"] = calls;
		options["PUT"] = puts;
		return options;
	}
}