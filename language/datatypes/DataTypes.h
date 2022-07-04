
#ifndef KIRAAK_DATATYPES_H
#define KIRAAK_DATATYPES_H


#include "../errors/Errors.h"

#include <cmath>
#include <memory>
#include <variant>


using NumberValue = std::variant<int, double>;


struct DataType {
    virtual ~DataType() = default;
    virtual std::string toString() = 0;

    friend std::ostream& operator << (std::ostream&, DataType*);
};


class Number: public DataType {
    NumberValue value;
    const ParsePosition &start, &end;

public:
    Number(NumberValue value, const ParsePosition &start, const ParsePosition &end):
        value(value), start(start), end(end) {}

    std::string toString() override;

    std::shared_ptr<Number> operator + (const Number&);
    std::shared_ptr<Number> operator - (const Number&);
    std::shared_ptr<Number> operator * (const Number&);
    std::shared_ptr<Number> operator ^ (const Number&);
    std::shared_ptr<Number> operator / (const Number&);
    std::shared_ptr<Number> operator % (const Number&);

    Token getErrToken() { return { start, end }; }
};


#endif //KIRAAK_DATATYPES_H
