#ifndef _STRUCTURES_H
#define _STRUCTURES_H

#include <algorithm>
#include <string>
#include <vector>
#include <chrono>
#include <ostream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <unordered_set>
using milliseconds = std::chrono::milliseconds;


namespace Structures {

    struct Quotes {

        std::vector<float> 
            m_open, 
            m_high, 
            m_low, 
            m_close;
        std::vector<long int> 
            m_volume;
        std::vector<time_t> 
            m_unix;

        Quotes(
            std::vector<float> open,
            std::vector<float> high,
            std::vector<float> low,
            std::vector<float> close,
            std::vector<long int> volume,
            std::vector<time_t> _unix
        ) :
            m_open(open),
            m_high(high),
            m_low(low),
            m_close(close),
            m_volume(volume),
            m_unix(_unix)
        {};

        friend std::ostream& operator<<(
            std::ostream& stream,
            const Structures::Quotes& q) 
        {
            const unsigned int size = q.m_close.size();
            stream << "=======================================================================\n";
            stream << "============================== QUOTE CONTENT ==========================\n";
            stream << "=======================================================================\n\n";
            stream << "\tQueried info:\n";
            stream << "\t----------------------------\n";
            stream << "\tObservations   \t: " << size << "\n";
            stream << "\tStarting (Unix)\t: " << q.m_unix[0] << "\n";
            stream << "\tEnding (Unix)  \t: " << q.m_unix[size - 1] << "\n\n\n";
            return stream;
        };

    };

    struct Option {

        std::optional<bool> 
            m_inTheMoney;
        std::optional<std::string> 
            m_contractSymbol,
            m_currency, 
            m_contractSize;
        std::optional<float> 
            m_strike, 
            m_lastPrice, 
            m_change, 
            m_volume, 
            m_bid, 
            m_ask, 
            m_percentChange, 
            m_openInterest, 
            m_impliedVolatility;
        std::optional<time_t> 
            m_expiration, 
            m_lastTradeDate;

        Option() = default;

        Option(
            bool inTheMoney, 
            std::string contractSymbol,
            std::string currency, 
            std::string contractSize,
            float strike, 
            float lastPrice, 
            float change,
            float percentChange, 
            float openInterest, 
            float bid,
            float ask, 
            float impliedVolatility, 
            float volume,
            time_t expiration, 
            time_t lastTradeDate
        ): 
            m_inTheMoney(inTheMoney), 
            m_contractSymbol(contractSymbol),
            m_currency(currency), 
            m_contractSize(contractSize),
            m_strike(strike), 
            m_lastPrice(lastPrice), 
            m_change(change),
            m_bid(bid), 
            m_ask(ask), 
            m_percentChange(percentChange),
            m_openInterest(openInterest), 
            m_impliedVolatility(impliedVolatility),
            m_volume(volume), 
            m_expiration(expiration),
            m_lastTradeDate(lastTradeDate) 
        {};

        friend std::ostream& operator<<(
            std::ostream& stream,
            const Structures::Option& opt)
        {
            stream <<    "=======================================================================\n";
            stream << "============================== OPTION CONTENT =========================\n";
            stream << "=======================================================================\n\n";
            stream << "\tQueried info:\n";
            stream << "\t----------------------------\n";
            stream << "\tSymbol        \t: " << opt.m_contractSymbol.value() << "\n";
            stream << "\tCurrency      \t: " << opt.m_currency.value() << "\n";
            stream << "\tExpiration    \t: " << opt.m_expiration.value() << "\n";
            stream << "\tI.V.          \t: " << opt.m_impliedVolatility.value() << "\n";
            stream << "\tBid           \t: " << opt.m_bid.value() << "\n";
            stream << "\tAsk           \t: " << opt.m_ask.value() << "\n\n\n";
            return stream;
        };
    };

    struct Profile {
        std::optional<std::string>
            m_address, 
            m_city, 
            m_state, 
            m_zip,
            m_country, 
            m_phone, 
            m_website, 
            m_industry,
            m_sector, 
            m_longBusinessSummary;
        std::optional<unsigned int> 
            m_fullTimeEmployees, 
            m_overallRisk;
        std::optional<nlohmann::json>
            m_companyOfficers;

        Profile() = default;
        Profile(
            std::string address,
            std::string city,
            std::string state,
            std::string zip,
            std::string country,
            std::string phone,
            std::string website,
            std::string industry,
            std::string sector,
            std::string longBusinessSummary,
            unsigned int fullTimeEmployees,
            unsigned int overallRisk,
            nlohmann::json companyOfficers
        ):
            m_address(address),
            m_city(city),
            m_state(state),
            m_zip(zip),
            m_country(country),
            m_phone(phone),
            m_website(website),
            m_industry(industry),
            m_sector(sector),
            m_longBusinessSummary(longBusinessSummary),
            m_fullTimeEmployees(fullTimeEmployees),
            m_overallRisk(overallRisk),
            m_companyOfficers(companyOfficers)
        {};

        friend std::ostream& operator<<(
            std::ostream& stream,
            const Structures::Profile& p) {
            stream << "=======================================================================\n";
            stream << "========================== SHOW PROFILE SUMMARY =======================\n";
            stream << "=======================================================================\n\n";
            stream << "\tCountry         \t: " << p.m_country.value() << "\n";
            stream << "\tState           \t: " << p.m_state.value() << "\n";
            stream << "\tCity            \t: " << p.m_city.value() << "\n";
            stream << "\tAdress          \t: " << p.m_address.value() << "\n";
            stream << "\tIndustry        \t: " << p.m_industry.value() << "\n";
            stream << "\tSector          \t: " << p.m_sector.value() << "\n\n\n";
            return stream;
        }

    };

    struct TimeitResult {

        std::size_t m_iters;
        milliseconds m_min;
        milliseconds m_max;
        milliseconds m_avg;
        milliseconds m_sum;

        TimeitResult(
            std::size_t iters,
            milliseconds min,
            milliseconds max,
            milliseconds avg, 
            milliseconds sum
        ): 
            m_iters(iters), 
            m_min(min),
            m_max(max), 
            m_avg(avg), 
            m_sum(sum) 
        {};

        friend std::ostream& operator<<(
            std::ostream& stream,
            const Structures::TimeitResult& t) 
        {
            stream << "=======================================================================\n";
            stream << "=========================== SHOW TIMEIT RESULTS =======================\n";
            stream << "=======================================================================\n\n";

            stream << "\tIterations completed\t: " << t.m_iters << "\n";
            stream << "\tTotal milliseconds\t:" << t.m_sum.count() << "\n";
            stream << "\tAverage milliseconds\t:" << t.m_avg.count() << "\n";
            stream << "\tMaxima milliseconds\t:" << t.m_max.count() << "\n";
            stream << "\tMinima milliseconds\t:" << t.m_min.count() << "\n\n\n";
            return stream;
        }
    };

    struct Response {
        std::string m_text;
        long m_status_code;

        Response(
            std::string text, 
            long status_code
        ): 
            m_text(text), 
            m_status_code(status_code) 
        {};

        friend std::ostream& operator<<(
            std::ostream& stream,
            const Response& r)
        {
            stream << "=======================================================================\n";
            stream << "========================== SHOW REQUESTS RESULTS ======================\n";
            stream << "=======================================================================\n\n";

            stream << "\tStatus Code       \t: " << r.m_status_code << "\n\n\n";
            return stream;
        }
    };

    struct News {
        std::optional<std::string> m_title, m_publisher, m_link;
        std::optional<time_t> m_providerPublishTime;
        std::optional<std::vector<std::string>> m_relatedTickers;

        News(
            std::optional<std::string> title,
            std::optional<std::string> publisher,
            std::optional<std::string> link,
            std::optional<time_t> providerPublishTime,
            std::optional<std::vector<std::string>> relatedTickers
        ) :
            m_title(title),
            m_publisher(publisher),
            m_link(link),
            m_providerPublishTime(providerPublishTime),
            m_relatedTickers(relatedTickers) {};

        friend std::ostream& operator<<(
            std::ostream& stream,
            const News& n) {
            
            stream << "=============================================================================================\n";
            stream << "======================================= SHOW NEWS RESULTS ===================================\n";
            stream << "=============================================================================================\n\n";

            stream << "\tTitle           \t: " << n.m_title.value() << "\n";
            stream << "\tPublisher       \t: " << n.m_publisher.value() << "\n";
            stream << "\tLink            \t: " << n.m_link.value() << "\n";
            stream << "\tPublish Time    \t: " << n.m_providerPublishTime.value() << "\n";
            stream << "\tRelated Tickers \t: {";
            for (auto& relatedTicker : n.m_relatedTickers.value()) stream << relatedTicker << ',';
            stream << "}\n\n\n";
            return stream;

        };
    };
}

#endif // #ifndef _STRUCTURES_H