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
            const Structures::Quotes& q
            ) {
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

        bool m_in_the_money;
        std::string m_contract_symbol, m_currency,
            m_contract_size;
        float m_strike, m_last_price, m_change,
            m_percent_change, m_open_interest,
            m_bid, m_ask, m_implied_volatility,
            m_volume;
        time_t m_expiration, m_last_trade_date;

        Option() = default;

        Option(
            bool in_the_money, std::string constract_symbol,
            std::string currency, std::string contract_size,
            float strike, float last_price, float change,
            float percentage_change, float open_interest,
            float bid, float ask, float implied_volatility,
            float volume, time_t expiration, time_t last_trade_date)
            : m_in_the_money(in_the_money), m_contract_symbol(constract_symbol),
            m_currency(currency), m_contract_size(contract_size), m_strike(strike),
            m_last_price(last_price), m_change(change), m_bid(bid), m_ask(ask),
            m_percent_change(percentage_change), m_open_interest(open_interest),
            m_implied_volatility(implied_volatility), m_volume(volume),
            m_expiration(expiration), m_last_trade_date(last_trade_date) {}
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
            const Structures::TimeitResult& t
            ) {
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
}
