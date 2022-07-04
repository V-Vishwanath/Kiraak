
#ifndef KIRAAK_PARSEPOSITION_H
#define KIRAAK_PARSEPOSITION_H

#include <iostream>

struct ParsePosition {
    std::size_t index, line, col;

    void nextLine() {
        index++;
        line++;
        col = 0;
    }

    void operator++ (int) {
        index++;
        col++;
    }

    ParsePosition(): index(0), line(0), col(0) {}
};

#endif //KIRAAK_PARSEPOSITION_H
