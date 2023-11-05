#include "date.h"
#include <string>
#include <vector>
#ifndef util
#    define util

static bool wildcard_match(std::string s, std::string p) {
    int m = s.size();
    int n = p.size();
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1));
    dp[0][0] = true;
    for (int i = 1; i <= n; ++i) {
        if (p[i - 1] == '%') {
            dp[0][i] = true;
        }
        else {
            break;
        }
    }
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (p[j - 1] == '%') {
                dp[i][j] = dp[i][j - 1] | dp[i - 1][j];
            }
            else if (p[j - 1] == '_' || s[i - 1] == p[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            }
        }
    }
    return dp[m][n];
}

static void try_to_cast(AttrType to_type, bool nullable, Value& value) {
    if (to_type == INTS && value.attr_type() == CHARS) {
        int num = 0;
        std::istringstream ss(value.get_string());
        ss >> num;
        value.set_int(num);
    }
    else if (to_type == FLOATS && value.attr_type() == CHARS) {
        float num = 0;
        std::istringstream ss(value.get_string());
        ss >> num;
        value.set_float(num);
    }
    else if (to_type == DATES && value.attr_type() == CHARS) {
        int date = 0;
        string_to_date(value.get_string().c_str(), date);
        value.set_int(date);
    }
    else if (to_type == CHARS && value.attr_type() == INTS) {
        std::string str = std::to_string(value.get_int());
        value.set_string(str.c_str());
    }
    else if (to_type == CHARS && value.attr_type() == FLOATS) {
        std::string str = std::to_string(value.get_float());
        value.set_string(str.c_str());
    }
    else if (to_type == CHARS && value.attr_type() == DATES) {
        int date = value.get_int();
        std::string res = date_to_string(date);
        value.set_string(res.c_str());
    }
}
#endif