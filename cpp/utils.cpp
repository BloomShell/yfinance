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

        namespace Summary {
            const std::string v11 =
                "https://query2.finance.yahoo.com/v11/finance/quoteSummary/";
        }

        namespace Overall {
            std::vector<std::string> nans = {
                "#N/A", "NaN", "nan", "<NA>", "N/A", "n/a",
                "NA", "NULL", "null" };
        }
    }
}