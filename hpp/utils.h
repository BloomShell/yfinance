#pragma once
#include <vector>
#include <array>
#include <chrono>
#include <string>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <nlohmann/json.hpp>

namespace yfinance {

	namespace utils {

		namespace methods {

			std::string substring(
				const std::string& input,
				unsigned int start,
				unsigned int end
			);

			std::vector<int> findall(
				const std::vector<std::string>& v,
				const std::vector<std::string>& z
			);

		}

		namespace constants {

			namespace quotes {

				extern std::unordered_map<std::string, int> ranges;
				extern const std::string v8;
				typedef std::unordered_map<std::string, std::string> qmap;
				extern std::array<std::string, 14> intervals;
			}

			namespace general {

				extern std::vector<std::string> NaNs;
				typedef nlohmann::json response;
			}
		}

		namespace benchmarking {

			namespace timeit {

				typedef std::chrono::milliseconds milliseconds;

				struct Result {

					milliseconds m_min;
					milliseconds m_max;
					milliseconds m_avg;
					milliseconds m_sum;

					Result(milliseconds min, milliseconds max, milliseconds avg,
						milliseconds sum)
						: m_min(min), m_max(max), m_avg(avg), m_sum(sum) {};

				};

				template<typename Function, typename ... Args>
				Result Timeit(uint16_t iters, bool verbose, Function& f, Args&& ... args) noexcept(false) {

					if (iters < 1) throw std::runtime_error("Iters must be >= 1.");

					typedef std::chrono::time_point<std::chrono::high_resolution_clock> time_point;
					typedef std::vector<std::chrono::milliseconds> Clocks;

					Clocks clocks;
					clocks.reserve(iters);

					for (int it = 0; it < iters; it++) {
						time_point t0 = std::chrono::high_resolution_clock::now();
						f(std::forward<Args>(args)...);
						time_point t1 = std::chrono::high_resolution_clock::now();
						clocks.emplace_back(
							std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count());
					}

					milliseconds max = *std::max_element(clocks.begin(), clocks.end());
					milliseconds min = *std::min_element(clocks.begin(), clocks.end());
					milliseconds sum = std::accumulate(clocks.begin(), clocks.end(), milliseconds(0));
					milliseconds avg = sum / clocks.size();

					if (verbose) {
						std::cout << "=======================================================================\n";
						std::cout << "=========================== SHOW TIMEIT RESULTS =======================\n";
						std::cout << "=======================================================================\n\n";

						std::cout << "\tIterations completed\t: " << iters << "\n";
						std::cout << "\tTotal milliseconds\t: " << sum << "\n";
						std::cout << "\tAverage milliseconds\t: " << avg << "\n";
						std::cout << "\tMaxima milliseconds\t: " << max << "\n";
						std::cout << "\tMinima milliseconds\t: " << min << "\n\n\n";
					}

					return Result(min, max, avg, sum);
				}

			}
		}


	}
}