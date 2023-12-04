#include <base.h>
#include <benchmark.h>


void news() {

	yfinance::Symbol* symbol;
	symbol = new yfinance::Symbol("AAPL");

	// Getting news for the symbol;
	auto news = symbol->get_news();

	// Printing the first news;
	std::cout << news[0];

	// Benchmarking;
	auto f = std::bind(&yfinance::Symbol::get_news, symbol);
	auto benchmarkResult = Benchmarking::Timeit(10, f);
	std::cout << benchmarkResult;
}