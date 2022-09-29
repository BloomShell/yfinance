#include "../hpp/utils.h"
#include "../hpp/base.h"
#include "../hpp/structures.h"


int main(int argc, char** argv) {

	// Initialize the Ticker object:
	yfinance::Symbol* tk;
	tk = new yfinance::Symbol("AAPL");

	// Loading quotes into struct:
	auto quotes = tk->get_quotes("5m");

	// Print Quotes content:
	std::cout << quotes;

	// Benchmarking:
	auto f = std::bind(
		&yfinance::Symbol::get_quotes, tk,
		std::placeholders::_1, std::placeholders::_2,
		std::placeholders::_3, std::placeholders::_4);

	auto timeit = Utils::Benchmarking::Timeit(
		100, f, "1h", -1, -1, ",");
	
	// Printing benchmark results:
	std::cout << timeit;
}