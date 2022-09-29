#include "../hpp/utils.h"
#include "../hpp/structures.h"


namespace Utils {

    namespace Statics {

        namespace Quotes {
            const std::string v8 =
                "https://query2.finance.yahoo.com/v8/finance/chart/";

            std::unordered_map<std::string, int> ranges = {
                {"1m",7}, {"2m",60}, {"5m",60}, {"15m",60}, {"30m",60},
                {"90m",60}, {"60m",730}, {"1h",730} };

            std::array<std::string, 14> intervals = { "1m","2m","5m","15m",
                "30m","60m","90m","1h","1d","5d","1wk","1mo","3mo" };
        }

        namespace Options {
            const std::string v7 =
                "https://query2.finance.yahoo.com/v7/finance/options/";
        }

        namespace Overall {
            std::vector<std::string> nans = {
                "#N/A", "NaN", "nan", "<NA>", "N/A", "n/a",
                "NA", "NULL", "null" };
        }
    }

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
        };
    }
}