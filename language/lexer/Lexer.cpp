
#include "Lexer.h"


char Lexer::_currChar() const {
    return _currPos.index < _srcCode.length() ? _srcCode[_currPos.index] : '\0';
}


void Lexer::_genNumberToken(LexerResult &res) {
    bool decimal = false;
    ParsePosition startPos = _currPos;

    while (true) {
        char chr = _currChar();

        if (chr == '.') {
            if (decimal) {
                res.error.emplace(IllegalCharError(ErrorMsg::DECIMAL_AFTER_DECIMAL, Token(startPos, _currPos)));
                return;
            }

            decimal = true;
        }

        else if (!isdigit(chr)) break;
        _currPos++;
    }

    auto number = std::string(_srcCode.substr(startPos.index, _currPos.index - startPos.index));
    res.tokens.emplace_back(
        decimal ?
            Token(TOKENTYPE::DOUBLE, std::stod(number), startPos, _currPos) :
            Token(TOKENTYPE::INT, std::stoi(number), startPos, _currPos)
    );
}


void Lexer::_getNextToken(LexerResult &res) {
start:
    char chr = _currChar();

    if (chr == '\0') res.tokens.emplace_back(Token(TOKENTYPE::EOF_, _currPos));

    else if (chr == ' ' || chr == '\t' || chr == '\n') {
        chr == '\n' ? _currPos.nextLine() : _currPos++;
        goto start;
    }

    else if (isdigit(chr)) _genNumberToken(res);

    else {
        ParsePosition posStart = _currPos;
        _currPos++;

        switch (chr) {
            case '+': res.tokens.emplace_back(Token(TOKENTYPE::ADD, posStart)); break;
            case '-': res.tokens.emplace_back(Token(TOKENTYPE::SUB, posStart)); break;
            case '*': res.tokens.emplace_back(Token(TOKENTYPE::MUL, posStart)); break;
            case '/': res.tokens.emplace_back(Token(TOKENTYPE::DIV, posStart)); break;
            case '^': res.tokens.emplace_back(Token(TOKENTYPE::POW, posStart)); break;
            case '%': res.tokens.emplace_back(Token(TOKENTYPE::MOD, posStart)); break;

            case '(': res.tokens.emplace_back(Token(TOKENTYPE::LPAREN, posStart)); break;
            case ')': res.tokens.emplace_back(Token(TOKENTYPE::RPAREN, posStart)); break;

            default:
                res.error.emplace(IllegalCharError(ErrorMsg::UNEXPECTED_CHAR(chr), Token(posStart)));
                return;
        }
    }
}


LexerResult Lexer::getTokens()  {
    LexerResult res;

    while (true) {
        _getNextToken(res);
        if (res.error.has_value() || res.tokens.back().type == TOKENTYPE::EOF_) break;
    }

    return res;
}
