#include "hpp/utils.h"
#include "hpp/base.h"
#include "hpp/structures.h"
#include <iostream>

int main(int argc, char **argv) {

	std::string symbol = "AAPL";
	std::string interval = "1d";

	auto r = yfinance::base::quotes::get_quotes(std::move(symbol), std::move(interval));
	auto result = yfinance::structures::quotes::ohlcv().load(r, ",");
	yfinance::structures::quotes::ohlcv().summary(result, symbol, interval);
}