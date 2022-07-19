
#ifndef KIRAAK_TOKEN_H
#define KIRAAK_TOKEN_H


#include "TokenTypes.h"
#include "ParsePosition.h"

#include <string>
#include <variant>
#include <optional>


using TokenValue = std::variant<bool, int, double, std::string>;


struct Token {
    TOKENTYPE type;
    ParsePosition posStart, posEnd;
    std::optional<TokenValue> value;


    Token(const TOKENTYPE &type, const ParsePosition &posStart, const ParsePosition &posEnd):
        type(type), posStart(posStart), posEnd(posEnd) {}

    Token(const TOKENTYPE &type, const ParsePosition &posStart):
        Token(type, posStart, posStart) { posEnd++; }

    explicit Token(ParsePosition &pos):
        Token(TOKENTYPE::ERR_, pos) {}

    Token(const TOKENTYPE &type, const TokenValue &value, const ParsePosition &posStart, const ParsePosition &posEnd):
        Token(type, posStart, posEnd) { this->value = value; }

    Token(const TOKENTYPE &type, const TokenValue &value, const ParsePosition &posStart):
        Token(type, value, posStart, posStart) {}

    Token(const ParsePosition &start, const ParsePosition &end):
        Token(TOKENTYPE::ERR_, start, end) {}
};


#endif //KIRAAK_TOKEN_H
