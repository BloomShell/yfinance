/**
 * @file main.cpp
 * @author Oliver Ofenloch (57812959+ofenloch@users.noreply.github.com)
 * @brief
 * @version 0.1
 * @date 2023-12-04
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <base.h>
#include <benchmark.h>
int main(int /*argc*/, char * /*argv*/[])
{
    int iReturnCode = 0;

    //
    // demo/news.cpp
    //
	yfinance::Symbol* symbol;
	symbol = new yfinance::Symbol("AAPL");
	// Getting news for the symbol;
	auto news = symbol->get_news();
	// Printing the first news;
	std::cout << news[0];
	// // Benchmarking;
	// auto f = std::bind(&yfinance::Symbol::get_news, symbol);
	// auto benchmarkResult = Benchmarking::Timeit(10, f);
	// std::cout << benchmarkResult;



    //
    // demo/options.cpp
    //
    // Initialize the Ticker object:
    yfinance::Symbol *tk;
    tk = new yfinance::Symbol("GS");
    // Loading options into struct:
    auto options = tk->get_options();
    // Print Option:
    std::cout << options["calls"][0];
    // // Benchmarking:
    // auto f = std::bind(&yfinance::Symbol::get_options, tk);
    // auto timeit = Benchmarking::Timeit(10, f);
    // // Printing benchmark results:
    // std::cout << timeit;

    //
    // demo/quotes.cpp
    //
	// Initialize the Ticker object:
	//yfinance::Symbol* tk;
	tk = new yfinance::Symbol("AAPL");
	// Loading quotes into struct:
	auto quotes = tk->get_quotes("1d");
	// Print Quotes content:
	std::cout << quotes;
	// // Benchmarking:
	// auto f = std::bind(
	// 	&yfinance::Symbol::get_quotes, tk,
	// 	std::placeholders::_1, std::placeholders::_2,
	// 	std::placeholders::_3, std::placeholders::_4);
	// auto timeit = Benchmarking::Timeit(100, f, "1h", -1, -1, ",");
	// // Printing benchmark results:
	// std::cout << timeit;

    //
    // demo/summary.cpp
    //
	// Initialize the Ticker object:
	//yfinance::Symbol* tk;
	tk = new yfinance::Symbol("GS");
	// Loading assetProfile into struct:
	auto profile = tk->get_profile();
	// Print assetProfile:
	std::cout << profile;
	// Loading Module (quoteSummary):
	auto quoteSummary = tk->get_summary("financialData");
	// Print Module:
	for (auto& [k, v] : quoteSummary.items())
		std::cout << k << ':' << v << "\n";



    return iReturnCode;
}