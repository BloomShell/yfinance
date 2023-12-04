#ifndef _BASE_H_
#define _BASE_H_
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <nlohmann/json.hpp>
#include <algorithm>
#include <string>
#include <regex>
#include <cpr/cpr.h>
#include <structures.h>
#include <utils.h>
using json = nlohmann::json;


namespace yfinance {

    class Symbol {

    private:

        // Member values:
        std::string m_symbol;

    public:

        // Constructors:
        Symbol(
            std::string symbol
        ):
            m_symbol(symbol) {}

        // Member functions:
        Structures::Quotes get_quotes(
            const std::string&& interval,
            time_t&& start = -1,
            time_t&& end = -1,
            const std::string sep = ","
        );

        Utils::Types::Options get_options(
        );

        Structures::Profile get_profile(
        );

        nlohmann::json get_summary(
            const std::string&& module
        );

        std::vector<Structures::News> get_news(
        );

    };
}

#endif // #ifndef _BASE_H_