
#ifndef KIRAAK_NUMBER_H
#define KIRAAK_NUMBER_H


#include "Boolean.h"
#include "../errors/Errors.h"

#include <cmath>
#include <variant>


class Number: public DataType {
    using NumberValue = std::variant<int, double>;
    NumberValue value;

    std::shared_ptr<Number> _divide(const Number& other, bool withDecimal = true) {
        std::shared_ptr<Number> res;

        std::visit([&res, &withDecimal, this, &other](auto &val1, auto &val2) {
            if (val2 == 0) res = nullptr;
            else {
                double q = val1 / double(val2);
                res = std::make_shared<Number>(withDecimal ? q : int(q), this->posStart, other.posEnd);
            }
        }, value, other.value);

        return res;
    }

    template<typename resDataType = Number, typename BinOp>
    std::shared_ptr<resDataType> _binaryOp(const Number& other, BinOp opFunc) {
        std::shared_ptr<resDataType> res;

        std::visit([&res, this, &other, &opFunc](auto &val1, auto &val2) {
            res = std::make_shared<resDataType>(opFunc(val1, val2), this->posStart, other.posEnd);
        }, value, other.value);

        return res;
    }


public:
    Number(const Number& other): DataType(other.posStart, other.posEnd), value(other.value) {}
    Number(NumberValue value, ParsePosition &start, ParsePosition &end): DataType(start, end), value(value) {}


    TYPE Type() override { return TYPE::NUMBER; }
    std::string toString() override {
        std::stringstream ss;
        std::visit([&ss](auto &val) { ss << val; }, value);
        return ss.str();
    }


    // Unary -
    std::shared_ptr<Number> operator - () {
        std::shared_ptr<Number> res;

        std::visit([&res, this](auto &val) {
            res = std::make_shared<Number>(-val, this->posStart, this->posEnd);
        }, value);

        return res;
    }


    // Arithmetic operators
    std::shared_ptr<Number> operator + (const Number &other) {
        return _binaryOp(other, std::plus<>());
    }

    std::shared_ptr<Number> operator - (const Number &other) {
        return _binaryOp(other, std::minus<>());
    }

    std::shared_ptr<Number> operator * (const Number &other) {
        return _binaryOp(other, std::multiplies<>());
    }

    std::shared_ptr<Number> operator ^ (const Number &other) {
        return _binaryOp(other, pow);
    }

    std::shared_ptr<Number> operator % (const Number &other) {
        return _binaryOp(other, fmod);
    }

    std::shared_ptr<Number> operator / (const Number &other) { return _divide(other); }
    std::shared_ptr<Number> divideAsInt(const Number &other) { return _divide(other, false); }


    // Comparison operators
    std::shared_ptr<Boolean> operator == (const Number &other) {
        return _binaryOp<Boolean>(other, std::equal_to<>());
    }

    std::shared_ptr<Boolean> operator != (const Number &other) {
        return _binaryOp<Boolean>(other, std::not_equal_to<>());
    }

    std::shared_ptr<Boolean> operator < (const Number &other) {
        return _binaryOp<Boolean>(other, std::less<>());
    }

    std::shared_ptr<Boolean> operator > (const Number &other) {
       return _binaryOp<Boolean>(other, std::greater<>());
    }

    std::shared_ptr<Boolean> operator <= (const Number &other) {
        return _binaryOp<Boolean>(other, std::less_equal<>());
    }

    std::shared_ptr<Boolean> operator >= (const Number &other) {
        return _binaryOp<Boolean>(other, std::greater_equal<>());
    }
};

#endif //KIRAAK_NUMBER_H
