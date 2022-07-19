
#ifndef KIRAAK__DATATYPE_H
#define KIRAAK__DATATYPE_H


#include "../token/ParsePosition.h"


class DataType {
protected:
    DataType(ParsePosition &start, ParsePosition &end): posStart(start), posEnd(end) {}
    DataType(): posStart(ParsePosition::DEFINED_CONST), posEnd(ParsePosition::DEFINED_CONST) {}

public:
    ParsePosition &posStart, &posEnd;

    enum class TYPE {
        NONE,
        NUMBER,
        BOOLEAN,
    };

    virtual TYPE Type() = 0;
    virtual std::string toString() = 0;

    void setPos(const ParsePosition &start, const ParsePosition &end) {
        posStart = start;
        posEnd = end;
    }

    [[nodiscard]] Token getErrToken() const {
        return {posStart, posEnd };
    }
};


struct None : public DataType {
    None(): DataType() {}
    None(ParsePosition &start, ParsePosition &end): DataType(start, end) {}

    TYPE Type() override { return TYPE::NONE; }
    std::string toString() override { return "Khaali"; }
};


#endif //KIRAAK__DATATYPE_H
