#include "../hpp/base.h"
#include "../hpp/benchmark.h"


void options(int argc, char** argv) {

	// Initialize the Ticker object:
	yfinance::Symbol* tk;
	tk = new yfinance::Symbol("GS");

	// Loading options into struct:
	auto options = tk->get_options();

	// Print Quotes content:
	std::cout << options;

	// Benchmarking:
	auto f = std::bind(
		&yfinance::Symbol::get_options, tk);

	auto timeit = Benchmarking::Timeit(
		10, f);

	// Printing benchmark results:
	std::cout << timeit;
}