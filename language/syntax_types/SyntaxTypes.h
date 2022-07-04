
#ifndef KIRAAK_SYNTAXTYPES_H
#define KIRAAK_SYNTAXTYPES_H

#include <iostream>


enum TOKENTYPE {
    EOF_, ERR_,

    ADD, SUB, MUL, DIV, POW, MOD,

    LPAREN, RPAREN,

    INT, DOUBLE, STRING
};

std::ostream &operator << (std::ostream &, const TOKENTYPE &);


#endif //KIRAAK_SYNTAXTYPES_H
