#include <base.h>
#include <benchmark.h>


void summary(int argc, char** argv) {

	// Initialize the Ticker object:
	yfinance::Symbol* tk;
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

}