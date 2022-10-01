#pragma once
#include <algorithm>
#include <string>
#include <vector>
#include <chrono>
#include <ostream>
#include <iostream>
using milliseconds = std::chrono::milliseconds;



namespace Structures {

    struct Quotes {

        std::vector<float> m_open, m_high, m_low, m_close;
        std::vector<long int> m_volume;
        std::vector<time_t> m_unix;

        Quotes(
            std::vector<float> open, std::vector<float> high,
            std::vector<float> low, std::vector<float> close,
            std::vector<long int> volume, std::vector<time_t> unix
        )
            : m_open(open), m_high(high), m_low(low), m_close(close),
            m_volume(volume), m_unix(unix) {}

        friend std::ostream& operator<<(
            std::ostream& stream,
            const Structures::Quotes& q) 
        {
            const unsigned int size = q.m_close.size();
            stream << "=======================================================================\n";
            std::cout << "============================== QUOTE CONTENT ==========================\n";
            std::cout << "=======================================================================\n\n";
            std::cout << "\tQueried info:\n";
            std::cout << "\t----------------------------\n";
            std::cout << "\tObservations   \t: " << size << "\n";
            std::cout << "\tStarting (Unix)\t: " << q.m_unix[0] << "\n";
            std::cout << "\tEnding (Unix)  \t: " << q.m_unix[size - 1] << "\n\n\n";
            return stream;
        };

    };

    struct Option {

        std::optional<bool> m_inTheMoney;
        std::optional<std::string> m_contractSymbol,
            m_currency, m_contractSize;
        std::optional<float> m_strike, 
            m_lastPrice, m_change, m_volume, 
            m_bid, m_ask, m_percentChange, 
            m_openInterest, m_impliedVolatility;
        std::optional<time_t> m_expiration, 
            m_lastTradeDate;

        Option() = default;

        Option(
            bool inTheMoney, std::string contractSymbol,
            std::string currency, std::string contractSize,
            float strike, float lastPrice, float change,
            float percentChange, float openInterest, float bid,
            float ask, float impliedVolatility, float volume,
            time_t expiration, time_t lastTradeDate)
            : m_inTheMoney(inTheMoney), m_contractSymbol(contractSymbol),
            m_currency(currency), m_contractSize(contractSize),
            m_strike(strike), m_lastPrice(lastPrice), m_change(change),
            m_bid(bid), m_ask(ask), m_percentChange(percentChange),
            m_openInterest(openInterest), m_impliedVolatility(impliedVolatility),
            m_volume(volume), m_expiration(expiration),
            m_lastTradeDate(lastTradeDate) {};
    };

    struct TimeitResult {

        std::size_t m_iters;
        milliseconds m_min;
        milliseconds m_max;
        milliseconds m_avg;
        milliseconds m_sum;

        TimeitResult(
            std::size_t iters,
            milliseconds min, milliseconds max,
            milliseconds avg, milliseconds sum)
            : m_iters(iters), m_min(min),
            m_max(max), m_avg(avg), m_sum(sum) {};

        friend std::ostream& operator<<(
            std::ostream& stream,
            const Structures::TimeitResult& t) 
        {
            stream << "=======================================================================\n";
            stream << "=========================== SHOW TIMEIT RESULTS =======================\n";
            stream << "=======================================================================\n\n";

            stream << "\tIterations completed\t: " << t.m_iters << "\n";
            stream << "\tTotal milliseconds\t: " << t.m_sum << "\n";
            stream << "\tAverage milliseconds\t: " << t.m_avg << "\n";
            stream << "\tMaxima milliseconds\t: " << t.m_max << "\n";
            stream << "\tMinima milliseconds\t: " << t.m_min << "\n\n\n";
            return stream;
        }
    };

    struct Response {
        std::string m_text;
        long m_status_code;

        Response(
            std::string text, long status_code)
            : m_text(text), m_status_code(status_code) {};

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
}