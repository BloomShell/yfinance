#include <base.h>
#include <utils.h>
#include <methods.h>


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
			boost::split(quotemap["unix"], Methods::substring(
				rjson["chart"]["result"][0]["timestamp"].dump(), 1, 2),
				boost::is_any_of(sep));
			for (auto& col : { "open", "high", "low", "close", "volume" }) {
				boost::split(quotemap[col], Methods::substring(
					rjson["chart"]["result"][0]["indicators"]
					["quote"][0][col].dump(), 1, 2), boost::is_any_of(sep));
			}

			// Deleting NaNs:
			std::vector<int> indexes = Methods::findall(quotemap["close"],
				Utils::Statics::Overall::nans);
			std::sort(indexes.rbegin(), indexes.rend());
			for (auto& col : { "open", "high", "low", "close", "volume", "unix" }) {
				for (auto& index : indexes) quotemap[col].erase(
					quotemap[col].begin() + index);
			}

			unsigned int size = quotemap["unix"].size();
			std::vector<float> open(size), high(size), low(size), close(size);
			std::vector<long int> volume(size);
			std::vector<time_t> _unix(size);

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
			std::transform(quotemap["unix"].begin(), quotemap["unix"].end(), _unix.begin(),
				[](const std::string& token) { return (time_t)std::stoll(token); });

			return Structures::Quotes(
				std::move(open),
				std::move(high),
				std::move(low),
				std::move(close),
				std::move(volume),
				std::move(_unix)
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
		cpr::Response r = cpr::Get(cpr::Url{
			Utils::Statics::Options::v7 + m_symbol });

		if ((r.status_code == 200) && (!r.text.empty())) {

			json rjson = nlohmann::json::parse(r.text);
			Utils::Types::Options options;
			std::vector<Structures::Option> calls, puts;
			options["calls"] = calls;
			options["puts"] = puts;

			// Emplacing raw response inside struct
			// applying casting:
			for (auto& kind : { "calls", "puts" }) {

				if (!rjson["optionChain"]["result"][0]
					["options"][0].contains(kind)) continue;
				
				auto& raw = rjson["optionChain"]["result"][0]
					["options"][0][kind];

				size_t size = raw.size();
				for (size_t i = 0; i < size; i++) {
					Structures::Option option;
					for (auto& [key, val] : raw[i].items()) {
						// As the response from YFINANCE API may be 
						// partial, Option() is default initialized
						// and items are added one at time;

						// Booleans:
						if (key == "inTheMoney") option.m_inTheMoney =
							std::move((bool)val);

						// Strings:
						if (key == "contractSymbol") option.m_contractSymbol =
							std::move(val);
						if (key == "currency") option.m_currency =
							std::move(val);
						if (key == "contractSize") option.m_contractSize =
							std::move(val);

						// Floats:
						if (key == "strike") option.m_strike =
							std::move(std::stof(val.dump()));
						if (key == "lastPrice") option.m_lastPrice =
							std::move(std::stof(val.dump()));
						if (key == "change") option.m_change =
							std::move(std::stof(val.dump()));
						if (key == "percentChange") option.m_percentChange =
							std::move(std::stof(val.dump()));
						if (key == "openInterest") option.m_openInterest =
							std::move(std::stof(val.dump()));
						if (key == "bid") option.m_bid =
							std::move(std::stof(val.dump()));
						if (key == "ask") option.m_ask =
							std::move(std::stof(val.dump()));
						if (key == "impliedVolatility") option.m_impliedVolatility =
							std::move(std::stof(val.dump()));

						// Time_t
						if (key == "expiration") option.m_expiration =
							std::move((time_t)std::stoll(val.dump()));
						if (key == "lastTradeDate") option.m_lastTradeDate =
							std::move((time_t)std::stoll(val.dump()));
					}
					options[kind].emplace_back(option);
				}
			}
			return options;
		}
		else {
			std::string error_message =
				"Request failed with status code: " + r.status_code;
			throw std::runtime_error(error_message);
		}
	}

	Structures::Profile Symbol::get_profile(
	) {
		cpr::Response r = cpr::Get(cpr::Url{
			Utils::Statics::Summary::v11 + m_symbol },
			cpr::Parameters{ {"modules", "assetProfile"} });

		if ((r.status_code == 200) && (!r.text.empty())) {
			nlohmann::json quoteSummary = nlohmann::json::parse(r.text);
			nlohmann::json& moduleSummary = quoteSummary["quoteSummary"]
				["result"][0]["assetProfile"];

			return Structures::Profile(
				moduleSummary["address1"],
				moduleSummary["city"],
				moduleSummary["state"],
				moduleSummary["zip"],
				moduleSummary["country"],
				moduleSummary["phone"],
				moduleSummary["website"],
				moduleSummary["industry"],
				moduleSummary["sector"],
				moduleSummary["longBusinessSummary"],
				std::stoi(moduleSummary["fullTimeEmployees"].dump()),
				std::stoi(moduleSummary["overallRisk"].dump()),
				moduleSummary["companyOfficers"]
			);
		}
		else {
			std::string error_message =
				"Request failed with status code: " + r.status_code;
			throw std::runtime_error(error_message);
		}
		
	};

	nlohmann::json Symbol::get_summary(
		const std::string&& module
	) {
		cpr::Response r = cpr::Get(cpr::Url{
			Utils::Statics::Summary::v11 + m_symbol },
			cpr::Parameters{ {"modules", module} });
		
		if ((r.status_code == 200) && (!r.text.empty())) {
			nlohmann::json quoteSummary = nlohmann::json::parse(r.text);
			return quoteSummary["quoteSummary"]
				["result"][0][module];
		}
		else {
			std::string error_message =
				"Request failed with status code: " + r.status_code;
			throw std::runtime_error(error_message);
		}
	}

	std::vector<Structures::News> Symbol::get_news(
	) {
		cpr::Response r = cpr::Get(cpr::Url{
			Utils::Statics::News::v11 + m_symbol });

		if ((r.status_code == 200) && (!r.text.empty())) {
			nlohmann::json quoteSummary = nlohmann::json::parse(r.text);
			nlohmann::json& newsSummary = quoteSummary["news"];
			if (newsSummary.empty()) {
				std::string error_message =
					"No news found for symbol: " + m_symbol;
				throw std::runtime_error(error_message);
			}
			std::vector<Structures::News> nv;
			std::vector<std::string> t_relatedTickers;
			for (auto& n : newsSummary) {
				auto relatedTickers = n["relatedTickers"].dump();
				boost::split(t_relatedTickers, relatedTickers.substr(1,
					relatedTickers.size() - 2), boost::is_any_of(","));
				std::for_each(t_relatedTickers.begin(), t_relatedTickers.end(),
					[&](std::string& s) { s = std::regex_replace(
						s, std::regex("[^\\w\\d\\.]+"), ""); });
				nv.emplace_back(Structures::News(n["title"], 
					n["publisher"], n["link"], (time_t)std::stol(
					n["providerPublishTime"].dump()),
					t_relatedTickers));
			};
			return nv;
		}
		else {
			std::string error_message =
				"Request failed with status code: " + r.status_code;
			throw std::runtime_error(error_message);
		}
	}
}