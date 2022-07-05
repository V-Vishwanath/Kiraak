
#include "DataTypes.h"


std::ostream& operator << (std::ostream &os, DataType *dataType) {
    if (auto data = dynamic_cast<Number*>(dataType))
        return os << data->toString();

    return os;
}


std::string Number::toString() {
    std::stringstream ss;
    std::visit([&ss](auto &val) { ss << val; }, value);
    return ss.str();
}


std::shared_ptr<Number> Number::operator + (const Number &other) {
    std::shared_ptr<Number> res;

    std::visit([&res, this, &other](auto &val1, auto &val2) {
        res = std::make_shared<Number>(val1 + val2, this->_start, other._end);
    }, value, other.value);

    return res;
}

std::shared_ptr<Number> Number::operator - (const Number &other) {
    std::shared_ptr<Number> res;

    std::visit([&res, this, &other](auto &val1, auto &val2) {
        res = std::make_shared<Number>(val1 - val2, this->_start, other._end);
    }, value, other.value);

    return res;
}

std::shared_ptr<Number> Number::operator * (const Number &other) {
    std::shared_ptr<Number> res;

    std::visit([&res, this, &other](auto &val1, auto &val2) {
        res = std::make_shared<Number>(val1 * val2, this->_start, other._end);
    }, value, other.value);

    return res;
}

std::shared_ptr<Number> Number::operator / (const Number &other) {
    std::shared_ptr<Number> res;

    std::visit([&res, this, &other](auto &val1, auto &val2) {
        if (val2 == 0) res = nullptr;
        else res = std::make_shared<Number>(val1 / val2, this->_start, other._end);
    }, value, other.value);

    return res;
}

std::shared_ptr<Number> Number::operator ^ (const Number &other) {
    std::shared_ptr<Number> res;

    std::visit([&res, this, &other](auto &val1, auto &val2) {
        double powVal = pow(val1, val2);
        bool bothInts = value.index() == other.value.index() && value.index() == 0;

        res = std::make_shared<Number>(
            bothInts ? int(round(powVal)) : powVal,
            this->_start, other._end
        );

    }, value, other.value);

    return res;
}

std::shared_ptr<Number> Number::operator % (const Number &other) {
    std::shared_ptr<Number> res;

    std::visit([&res, this, &other](auto &val1, auto &val2) {
        double powVal = fmod(val1, val2);
        bool bothInts = value.index() == other.value.index() && value.index() == 0;

        res = std::make_shared<Number>(
            bothInts ? int(round(powVal)) : powVal,
            this->_start, other._end
        );

    }, value, other.value);

    return res;
}
