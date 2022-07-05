
#ifndef KIRAAK_LEXER_H
#define KIRAAK_LEXER_H


#include "../utils/ResultWrappers.h"

#include <algorithm>


class Lexer {
    ParsePosition _currPos;
    std::string_view _srcCode;

    [[nodiscard]] char _currChar() const;

    void _getNextToken(LexerResult&);

    void _genNumberToken(LexerResult&);
    void _genKeywordOrVarToken(LexerResult &res);

public:
    explicit Lexer(std::string_view srcCode): _srcCode(srcCode) {}
    LexerResult getTokens();
};


#endif //KIRAAK_LEXER_H
