#pragma once
#include <string>
#include <vector>


namespace Methods {
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