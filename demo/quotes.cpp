#include "../hpp/utils.h"
#include "../hpp/base.h"
#include "../hpp/structures.h"

/*
	Testing the queries of Quotes for different
	time intervals.
	--------------------------------------------------------
*/


void quotes() {
	
	std::string symbol = "AAPL";
	std::string interval = "1h";

	std::cout << "Quering, Symbol: " << symbol << ", Interval: " << interval;
	std::cout << "\n---------------------------------------\n\n\n";

	// Initializing an empty Quote object.
	yfinance::structures::quotes::Quote quote(symbol);

	// Quering the response from yfinance 
	// and parsing as Json.
	auto response = yfinance::base::quotes::get_quotes(
		std::move(symbol), std::move(interval));
	
	// Loading the queried string within the Json
	// into the Quote struct.
	quote.load(response, ",");

	// Printing the summary.
	quote.summary();

	// Benchmarking.
	auto f = std::bind(
		&yfinance::structures::quotes::Quote::load, quote,
		std::placeholders::_1, std::placeholders::_2);
	
	yfinance::utils::benchmarking::timeit::Timeit(
		100, true, f, response, ",");
	
}