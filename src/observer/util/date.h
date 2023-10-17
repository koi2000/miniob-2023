#pragma once
#include "common/rc.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/value.h"
#include <sstream>
#include <stdint.h>
#include <stdio.h>
#include <string>

inline bool is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

inline RC string_to_date(const char* str, int32_t& date) {
    int year = 0;
    int month = 0;
    int day = 0;
    int ret = sscanf(str, "%d-%d-%d", &year, &month, &day);
    if (ret != 3) {
        return RC::INVALID_ARGUMENT;
    }
    if (year < 1900 || year > 9999 || month <= 0 || month > 12 || day <= 0 || day > 31) {
        return RC::INVALID_ARGUMENT;
    }
    int max_day_in_month[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    const int max_day = max_day_in_month[month - 1];
    if (day > max_day) {
        return RC::INVALID_ARGUMENT;
    }

    if (month == 2 && day > 28) {
        if (!((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)) {
            return RC::INVALID_ARGUMENT;
        }
    }
    date = year * 10000 + month * 100 + day;
    return RC::SUCCESS;
}

inline std::string date_to_string(int32_t date) {
    char buf[16] = {0};
    snprintf(buf, sizeof(buf), "%04d-%02d-%02d", date / 10000, (date % 10000) / 100, date % 100);
    std::string str(buf);
    return str;
}

inline bool check_date(int y, int m, int d) {
    static int mon[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    bool leap = (y % 400 == 0 || (y % 100 && y % 4 == 0));
    return y > 0 && (m > 0) && (m <= 12) && (d > 0) && (d <= ((m == 2 && leap) ? 1 : 0) + mon[m]);
}

inline void value_init_date(Value* value, int32_t date) {
    value->set_type(DATES);
    char* p = (char*)malloc(sizeof(date));
    memcpy(p, &date, sizeof(date));
    value->set_data(p, sizeof(date));
    free(p);
    p = nullptr;
}