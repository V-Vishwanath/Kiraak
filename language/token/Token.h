
#ifndef KIRAAK_TOKEN_H
#define KIRAAK_TOKEN_H


#include "ParsePosition.h"
#include "../syntax_types/SyntaxTypes.h"

#include <variant>
#include <optional>


using TokenValue = std::variant<int, double>;


struct Token {
    const TOKENTYPE type;
    ParsePosition posStart, posEnd;
    std::optional<TokenValue> value;


    Token(const TOKENTYPE &type, const ParsePosition &posStart, const ParsePosition &posEnd):
        type(type), posStart(posStart), posEnd(posEnd) {}

    Token(const TOKENTYPE &type, const ParsePosition &posStart): Token(type, posStart, posStart) { posEnd++; }


    Token(const TOKENTYPE &type, const TokenValue &value, const ParsePosition &posStart, const ParsePosition &posEnd):
        Token(type, posStart, posEnd) { this->value = value; }

    Token(const TOKENTYPE &type, const TokenValue &value, const ParsePosition &posStart):
        Token(type, value, posStart, posStart) {}


    explicit Token(ParsePosition &pos): Token(TOKENTYPE::ERR_, pos) {}
    Token(const ParsePosition &start, const ParsePosition &end): Token(TOKENTYPE::ERR_, start, end) {}

    friend std::ostream &operator << (std::ostream &, const Token &);
};


#endif //KIRAAK_TOKEN_H
