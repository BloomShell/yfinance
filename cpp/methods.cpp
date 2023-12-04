#include <algorithm>
#include <methods.h>


namespace Methods {
    std::string substring(
        const std::string& input,
        unsigned int start,
        unsigned int end
    ) {
        unsigned int n = input.size();
        return input.substr(start, n - end);
    }

    std::vector<int> findall(
        const std::vector<std::string>& v,
        const std::vector<std::string>& z
    ) {
        std::vector<int> indexes;
        auto it = v.begin();
        while ((it = std::find_if(it, v.end(), [&](const std::string x) {
            return std::find(z.begin(), z.end(), x) != z.end();
            })) != v.end()) {
            indexes.push_back(std::distance(v.begin(), it));
            it++;
        }
        return indexes;
    }
}