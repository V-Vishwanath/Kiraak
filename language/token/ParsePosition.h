
#ifndef KIRAAK_PARSEPOSITION_H
#define KIRAAK_PARSEPOSITION_H


#include <cstddef>


struct ParsePosition {
    static ParsePosition DEFINED_CONST;

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


inline ParsePosition ParsePosition::DEFINED_CONST; // NOLINT(cert-err58-cpp)

#endif //KIRAAK_PARSEPOSITION_H
