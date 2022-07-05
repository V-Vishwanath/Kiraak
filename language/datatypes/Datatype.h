
#ifndef KIRAAK_DATATYPE_H
#define KIRAAK_DATATYPE_H


#include "../token/ParsePosition.h"

#include <string>


class DataType {
    friend std::ostream& operator << (std::ostream&, DataType*);

protected:
    ParsePosition &_start, &_end;
    DataType(ParsePosition &start, ParsePosition &end): _start(start), _end(end) {}

public:
    virtual ~DataType() = default;
    virtual std::string toString() = 0;

    void setPos(const ParsePosition &start, const ParsePosition &end) {
        _start = start;
        _end = end;
    }
};


#endif //KIRAAK_DATATYPE_H
