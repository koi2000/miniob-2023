/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by WangYunlai on 2023/06/28.
//

#include "sql/parser/value.h"
#include "common/lang/comparator.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "storage/field/field.h"
#include "util/date.h"
#include <sstream>

const char* ATTR_TYPE_NAME[] = {"undefined", "chars", "ints", "null", "floats", "booleans", "dates"};

inline std::string float_to_string(float num) {
    std::ostringstream oss;
    oss << num;
    std::string str(oss.str());
    return str;
}

inline std::string int_to_string(int num) {
    std::ostringstream oss;
    oss << num;
    std::string str(oss.str());
    return str;
}

bool stringToNumber(const std::string& str, float& floatValue, int& intValue, bool& isFloat, bool& isInt) {
    // 初始化返回值
    isFloat = false;
    isInt = false;
    // 检查字符串是否为空
    if (str.empty()) {
        return false;
    }
    size_t i = 0;
    // 检查字符串是否以数字或正负号开头
    if (i < str.length() && (isdigit(str[i]) || str[i] == '-' || str[i] == '+')) {
        // 读取数字部分
        size_t end = i + 1;
        while (end < str.length() && (isdigit(str[end]) || str[end] == '.')) {
            end++;
        }
        std::string numericPart = str.substr(i, end - i);
        try {
            floatValue = std::stof(numericPart);      // 尝试将字符串转换为浮点数
            intValue = static_cast<int>(floatValue);  // 尝试将浮点数转换为整数

            // 判断是否是整数
            if (static_cast<float>(intValue) == floatValue) {
                isInt = true;
                isFloat = false;
            }
            else {
                isFloat = true;
                isInt = false;
            }
        }
        catch (const std::invalid_argument&) {
            return false;  // 无法转换为数字
        }
        catch (const std::out_of_range&) {
            return false;  // 数值超出范围
        }
        return true;
    }
    else {
        isInt = true;
        isFloat = false;
        intValue = 0;
        return false;  // 非数字开头的字符串
    }
}

const char* attr_type_to_string(AttrType type) {
    if (type >= UNDEFINED && type <= DATES) {
        return ATTR_TYPE_NAME[type];
    }
    return "unknown";
}
AttrType attr_type_from_string(const char* s) {
    for (unsigned int i = 0; i < sizeof(ATTR_TYPE_NAME) / sizeof(ATTR_TYPE_NAME[0]); i++) {
        if (0 == strcmp(ATTR_TYPE_NAME[i], s)) {
            return (AttrType)i;
        }
    }
    return UNDEFINED;
}

Value::Value(int val) {
    set_int(val);
}

Value::Value(float val) {
    set_float(val);
}

Value::Value(bool val) {
    set_boolean(val);
}

Value::Value(const char* s, int len /*= 0*/) {
    set_string(s, len);
}

void Value::set_data(char* data, int length) {
    switch (attr_type_) {
        case CHARS: {
            set_string(data, length);
        } break;
        case INTS:
        case DATES: {
            num_value_.int_value_ = *(int*)data;
            length_ = length;
        } break;
        case FLOATS: {
            num_value_.float_value_ = *(float*)data;
            length_ = length;
        } break;
        case BOOLEANS: {
            num_value_.bool_value_ = *(int*)data != 0;
            length_ = length;
        } break;
        default: {
            LOG_WARN("unknown data type: %d", attr_type_);
        } break;
    }
}
void Value::set_int(int val) {
    attr_type_ = INTS;
    num_value_.int_value_ = val;
    length_ = sizeof(val);
}

void Value::set_float(float val) {
    attr_type_ = FLOATS;
    num_value_.float_value_ = val;
    length_ = sizeof(val);
}
void Value::set_boolean(bool val) {
    attr_type_ = BOOLEANS;
    num_value_.bool_value_ = val;
    length_ = sizeof(val);
}

void Value::set_isNull(bool isNull) {
    // if (isNull) {
    //     attr_type_ = NULLS;
    // }
    isNull_ = isNull;
}

void Value::set_string(const char* s, int len /*= 0*/) {
    attr_type_ = CHARS;
    if (len > 0) {
        len = strnlen(s, len);
        str_value_.assign(s, len);
    }
    else {
        str_value_.assign(s);
    }
    length_ = str_value_.length();
}

void Value::set_value(const Value& value) {
    switch (value.attr_type_) {
        case INTS:
        case DATES: {
            set_int(value.get_int());
        } break;
        case FLOATS: {
            set_float(value.get_float());
        } break;
        case CHARS: {
            set_string(value.get_string().c_str());
        } break;
        case BOOLEANS: {
            set_boolean(value.get_boolean());
        } break;
        case UNDEFINED: {
            ASSERT(false, "got an invalid value type");
        } break;
    }
}

const char* Value::data() const {
    switch (attr_type_) {
        case CHARS: {
            return str_value_.c_str();
        } break;
        default: {
            return (const char*)&num_value_;
        } break;
    }
}

std::string Value::to_string() const {
    std::stringstream os;
    if (isNull()) {
        os << "NULL";
        return os.str();
    }
    switch (attr_type_) {
        case INTS: {
            os << num_value_.int_value_;
        } break;
        case FLOATS: {
            os << common::double_to_str(num_value_.float_value_);
        } break;
        case BOOLEANS: {
            os << num_value_.bool_value_;
        } break;
        case CHARS: {
            os << str_value_;
        } break;
        case DATES: {
            os << date_to_string(num_value_.int_value_);
        } break;
        default: {
            LOG_WARN("unsupported attr type: %d", attr_type_);
        } break;
    }
    return os.str();
}

int Value::compare(const Value& other) const {
    bool isInt = false;
    bool isFloat = false;
    int intValue = 0;
    float floatValue = 0;
    if (this->isNull() && !other.isNull()) {
        return -1;
    }
    else if (!this->isNull() && other.isNull()) {
        return 1;
    }
    else if (!this->isNull() && !other.isNull()) {
        return 0;
    }

    if (this->attr_type_ == other.attr_type_) {
        switch (this->attr_type_) {
            case INTS:
            case DATES: {
                return common::compare_int((void*)&this->num_value_.int_value_, (void*)&other.num_value_.int_value_);
            } break;
            case FLOATS: {
                return common::compare_float((void*)&this->num_value_.float_value_,
                                             (void*)&other.num_value_.float_value_);
            } break;
            case CHARS: {
                return common::compare_string((void*)this->str_value_.c_str(), this->str_value_.length(),
                                              (void*)other.str_value_.c_str(), other.str_value_.length());
            } break;
            case BOOLEANS: {
                return common::compare_int((void*)&this->num_value_.bool_value_, (void*)&other.num_value_.bool_value_);
            }
            default: {
                LOG_WARN("unsupported type: %d", this->attr_type_);
            }
        }
    }
    else if (this->attr_type_ == INTS && other.attr_type_ == DATES) {
        int this_data = this->num_value_.int_value_;
        return common::compare_int((void*)&this_data, (void*)&other.num_value_.int_value_);
    }
    else if (this->attr_type_ == DATES && other.attr_type_ == INTS) {
        int this_data = this->num_value_.int_value_;
        return common::compare_int((void*)&this_data, (void*)&other.num_value_.int_value_);
    }
    else if (this->attr_type_ == INTS && other.attr_type_ == FLOATS) {
        float this_data = this->num_value_.int_value_;
        return common::compare_float((void*)&this_data, (void*)&other.num_value_.float_value_);
    }
    else if (this->attr_type_ == FLOATS && other.attr_type_ == INTS) {
        float other_data = other.num_value_.int_value_;
        return common::compare_float((void*)&this->num_value_.float_value_, (void*)&other_data);
    }
    else if (this->attr_type_ == CHARS && other.attr_type_ == FLOATS) {
        std::string str = this->str_value_;
        stringToNumber(str, floatValue, intValue, isFloat, isInt);
        if (isInt) {
            floatValue = (float)intValue;
            return common::compare_float((void*)&floatValue, (void*)&other.num_value_.float_value_);
        }
        else if (isFloat) {
            return common::compare_float((void*)&floatValue, (void*)&other.num_value_.float_value_);
        }
    }
    else if (this->attr_type_ == CHARS && other.attr_type_ == INTS) {
        // this为char other为int
        std::string str = this->str_value_;
        stringToNumber(str, floatValue, intValue, isFloat, isInt);
        if (isInt) {
            return common::compare_int((void*)&intValue, (void*)&other.num_value_.int_value_);
        }
        else if (isFloat) {
            return common::compare_float((void*)&floatValue, (void*)&other.num_value_.float_value_);
        }
    }
    else if (this->attr_type_ == FLOATS && other.attr_type_ == CHARS) {
        std::string str = other.str_value_;
        stringToNumber(str, floatValue, intValue, isFloat, isInt);
        if (isInt) {
            floatValue = (float)intValue;
            return common::compare_float((void*)&this->num_value_.float_value_, (void*)&floatValue);
        }
        else if (isFloat) {
            return common::compare_float((void*)&other.num_value_.float_value_, (void*)&floatValue);
        }
    }
    else if (this->attr_type_ == INTS && other.attr_type_ == CHARS) {
        std::string str = other.str_value_;
        stringToNumber(str, floatValue, intValue, isFloat, isInt);
        if (isInt) {
            return common::compare_int((void*)&this->num_value_.int_value_, (void*)&intValue);
        }
        else if (isFloat) {
            return common::compare_float((void*)&other.num_value_.float_value_, (void*)&floatValue);
        }
    }

    LOG_WARN("not supported");
    return -1;  // TODO return rc?
}

int Value::get_int() const {
    switch (attr_type_) {
        case CHARS: {
            try {
                return (int)(std::stol(str_value_));
            }
            catch (std::exception const& ex) {
                LOG_TRACE("failed to convert string to number. s=%s, ex=%s", str_value_.c_str(), ex.what());
                return 0;
            }
        }
        case INTS:
        case DATES: {
            return num_value_.int_value_;
        }
        case FLOATS: {
            return (int)(num_value_.float_value_);
        }
        case BOOLEANS: {
            return (int)(num_value_.bool_value_);
        }
        default: {
            LOG_WARN("unknown data type. type=%d", attr_type_);
            return 0;
        }
    }
    return 0;
}

float Value::get_float() const {
    switch (attr_type_) {
        case CHARS: {
            try {
                return std::stof(str_value_);
            }
            catch (std::exception const& ex) {
                LOG_TRACE("failed to convert string to float. s=%s, ex=%s", str_value_.c_str(), ex.what());
                return 0.0;
            }
        } break;
        case INTS:
        case DATES: {
            return float(num_value_.int_value_);
        } break;
        case FLOATS: {
            return num_value_.float_value_;
        } break;
        case BOOLEANS: {
            return float(num_value_.bool_value_);
        } break;
        default: {
            LOG_WARN("unknown data type. type=%d", attr_type_);
            return 0;
        }
    }
    return 0;
}

std::string Value::get_string() const {
    return this->to_string();
}

bool Value::get_boolean() const {
    switch (attr_type_) {
        case CHARS: {
            try {
                float val = std::stof(str_value_);
                if (val >= EPSILON || val <= -EPSILON) {
                    return true;
                }

                int int_val = std::stol(str_value_);
                if (int_val != 0) {
                    return true;
                }

                return !str_value_.empty();
            }
            catch (std::exception const& ex) {
                LOG_TRACE("failed to convert string to float or integer. s=%s, ex=%s", str_value_.c_str(), ex.what());
                return !str_value_.empty();
            }
        } break;
        case INTS:
        case DATES: {
            return num_value_.int_value_ != 0;
        } break;
        case FLOATS: {
            float val = num_value_.float_value_;
            return val >= EPSILON || val <= -EPSILON;
        } break;
        case BOOLEANS: {
            return num_value_.bool_value_;
        } break;
        default: {
            LOG_WARN("unknown data type. type=%d", attr_type_);
            return false;
        }
    }
    return false;
}
