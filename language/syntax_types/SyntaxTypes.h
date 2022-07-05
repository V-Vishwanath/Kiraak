
#ifndef KIRAAK_SYNTAXTYPES_H
#define KIRAAK_SYNTAXTYPES_H

#include <iostream>
#include <unordered_set>


enum TOKENTYPE {
    EOF_, ERR_,

    ADD, SUB, MUL, DIV, POW, MOD,

    LPAREN, RPAREN,

    INT, DOUBLE, STRING,

    VAR, KEYWORD_
};


namespace KEYWORD {
    const std::string_view ASSIGNMENT = "boletho";

    inline std::unordered_set<std::string_view> list = { // NOLINT(cert-err58-cpp)
        ASSIGNMENT,
    };
}


std::ostream &operator << (std::ostream &, const TOKENTYPE &);


#endif //KIRAAK_SYNTAXTYPES_H
