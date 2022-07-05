
#ifndef KIRAAK_DATATYPES_H
#define KIRAAK_DATATYPES_H


#include "Datatype.h"
#include "../errors/Errors.h"

#include <cmath>
#include <memory>
#include <variant>


using NumberValue = std::variant<int, double>;


class Number: public DataType {
    NumberValue value;

public:
    Number(NumberValue value, ParsePosition &start, ParsePosition &end): DataType(start, end), value(value) {}

    std::string toString() override;

    std::shared_ptr<Number> operator + (const Number&);
    std::shared_ptr<Number> operator - (const Number&);
    std::shared_ptr<Number> operator * (const Number&);
    std::shared_ptr<Number> operator ^ (const Number&);
    std::shared_ptr<Number> operator / (const Number&);
    std::shared_ptr<Number> operator % (const Number&);

    Token getErrToken() { return {_start, _end }; }
};


#endif //KIRAAK_DATATYPES_H
