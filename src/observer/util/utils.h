#include "date.h"
#include <math.h>
#include <string>
#include <vector>
#ifndef util
#    define util
static std::string double2string(double v) {
    char buf[256];
    snprintf(buf, sizeof(buf), "%.2f", v);
    size_t len = strlen(buf);
    while (buf[len - 1] == '0') {
        len--;
    }
    if (buf[len - 1] == '.') {
        len--;
    }

    return std::string(buf, len);
}

static bool is_numeric_type(AttrType type) {
    return type == INTS || type == FLOATS;
}

static std::string value2string(const Value& value) {
    if (value.attr_type() == INTS) {
        return std::to_string(*(int*)value.data());
    }
    else if (value.attr_type() == FLOATS) {
        return double2string(static_cast<double>(*(float*)value.data()));
    }
    else if (value.attr_type() == CHARS) {
        return (char*)value.data();
    }
    return "";
}

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

static RC try_to_cast(AttrType to_type, bool nullable, Value& value) {
    RC rc = RC::SUCCESS;
    if (to_type == INTS && value.attr_type() == CHARS) {
        int num = 0;
        try {
            num = std::stoi(value.get_string());
        }
        catch (const std::invalid_argument& e) {
            rc = RC::INVALID_ARGUMENT;
        }
        catch (const std::out_of_range& e) {
            rc = RC::INVALID_ARGUMENT;
        }
        value.set_int(num);
        return rc;
    }
    else if (to_type == FLOATS && value.attr_type() == CHARS) {
        float num = 0;
        try {
            num = std::stoi(value.get_string());
        }
        catch (const std::invalid_argument& e) {
            rc = RC::INVALID_ARGUMENT;
        }
        catch (const std::out_of_range& e) {
            rc = RC::INVALID_ARGUMENT;
        }
        value.set_float(num);
        return rc;
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
    else if (to_type == INTS && value.attr_type() == FLOATS) {
        int int_val = std::round(*(float*)value.data());
        value.set_int(int_val);
    }
    else if (to_type == FLOATS && value.attr_type() == INTS) {
        float float_val = static_cast<float>(*(int*)value.data());
        value.set_float(float_val);
    }
    return rc;
}
#endif