#pragma once
#include "structures.h"
#include "utils.h"


namespace Benchmarking {
    template<typename Function, typename ... Args>
    Structures::TimeitResult Timeit(
        const std::size_t iters, const Function& f, Args&& ... args
    ) {
        if (iters < 1) throw std::runtime_error("Iters must be >= 1.");
        std::vector<std::chrono::milliseconds> durations;
        durations.reserve(iters);

        for (int it = 0; it < iters; it++) {
            time_point t0 = std::chrono::high_resolution_clock::now();
            f(std::forward<Args>(args)...);
            time_point t1 = std::chrono::high_resolution_clock::now();
            durations.emplace_back(
                std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count());
        }

        milliseconds max = *std::max_element(durations.begin(), durations.end());
        milliseconds min = *std::min_element(durations.begin(), durations.end());
        milliseconds sum = std::accumulate(durations.begin(), durations.end(), milliseconds(0));
        milliseconds avg = sum / durations.size();
        return Structures::TimeitResult(iters, min, max, avg, sum);
    };
}