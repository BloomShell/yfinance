#include "hpp/utils.h"
#include "hpp/base.h"
#include "hpp/structures.h"
#include <iostream>


int main(int argc, char **argv) {

	std::string symbol = "AAPL", interval = "1h";
	yfinance::structures::quotes::Quote quote(symbol);
	auto r = yfinance::base::quotes::get_quotes(
		std::move(symbol), std::move(interval));
	quote.load(r, ",");
	quote.summary();

	/* Timeit */
	auto f = std::bind(
		&yfinance::structures::quotes::Quote::load, quote,
		std::placeholders::_1, std::placeholders::_2);
	yfinance::utils::benchmarking::timeit::Timeit(
		100, true, f, r, ",");

}