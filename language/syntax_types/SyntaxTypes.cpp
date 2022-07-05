
#include "SyntaxTypes.h"


std::ostream &operator << (std::ostream &os, const TOKENTYPE &type) {
    switch (type) {
        case TOKENTYPE::EOF_: os << "::EOF::"; break;

        case TOKENTYPE::ADD: os << "ADD"; break;
        case TOKENTYPE::SUB: os << "SUB"; break;
        case TOKENTYPE::MUL: os << "MUL"; break;
        case TOKENTYPE::DIV: os << "DIV"; break;
        case TOKENTYPE::POW: os << "POW"; break;
        case TOKENTYPE::MOD: os << "MOD"; break;

        case TOKENTYPE::LPAREN: os << "LPAREN"; break;
        case TOKENTYPE::RPAREN: os << "RPAREN"; break;

        case TOKENTYPE::INT: os << "INT"; break;
        case TOKENTYPE::DOUBLE: os << "DOUBLE"; break;
        case TOKENTYPE::STRING: os << "STRING"; break;

        case TOKENTYPE::VAR: os << "VAR"; break;
        case TOKENTYPE::KEYWORD_: os << "KEYWORD_"; break;

        default: break;
    }

    return os;
}