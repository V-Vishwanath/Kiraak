
#ifndef KIRAAK_BOOLEAN_H
#define KIRAAK_BOOLEAN_H

#include "_Datatype.h"


class Boolean: public DataType {
    bool value;

public:
    Boolean(const Boolean& other): DataType(other.posStart, other.posEnd), value(other.value) {}
    Boolean(bool value, ParsePosition &start, ParsePosition &end) : DataType(start, end), value(value) {}

    TYPE Type() override { return TYPE::BOOLEAN; }
    std::string toString() override { return value ? "sahi" : "galat"; }


    explicit operator bool () const { return value; }

    std::shared_ptr<Boolean> operator ! () {
        return std::make_shared<Boolean>(!value, posStart, posEnd);
    }

    std::shared_ptr<Boolean> operator == (const Boolean &other) {
        return std::make_shared<Boolean>(value == other.value, posStart, other.posEnd);
    }

    std::shared_ptr<Boolean> operator != (const Boolean& other) {
        return std::make_shared<Boolean>(value != other.value, posStart, other.posEnd);
    }

    std::shared_ptr<Boolean> operator && (const Boolean &other) {
        return std::make_shared<Boolean>(value && other.value, posStart, other.posEnd);
    }

    std::shared_ptr<Boolean> operator || (const Boolean &other) {
        return std::make_shared<Boolean>(value || other.value, posStart, other.posEnd);
    }
};

#endif //KIRAAK_BOOLEAN_H
