
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
                res.error.emplace(ErrorMsg::DECIMAL_AFTER_DECIMAL, Token(startPos, _currPos));
                return;
            }

            decimal = true;
        }

        else if (!isdigit(chr)) break;
        _currPos++;
    }

    auto number = std::string(_srcCode.substr(startPos.index, _currPos.index - startPos.index));
    res.tokens.emplace_back(
        !decimal ?
            Token(TOKENTYPE::INT, std::stoi(number), startPos, _currPos) :
            Token(TOKENTYPE::DOUBLE, std::stod(number), startPos, _currPos)
    );
}


void Lexer::_genKeywordToken(ParsePosition &startPos, TOKENTYPE &kwType, LexerResult &res) {
    switch (kwType) {
        case TOKENTYPE::KW_BARAABAR: {
            if (res.tokens.empty()) break;

            Token &last = res.tokens.back();
            if (last.type != TOKENTYPE::KW_KE) break;

            // Expr1 Expr2 ke baraabar
            last.type = kwType;
            last.posEnd = _currPos;
            break;
        }

        case TOKENTYPE::KW_YA: {
            if (!res.tokens.empty()) {
                // Expr1 Expr2 jitta ya bada
                if (Token &last = res.tokens.back(); last.type == TOKENTYPE::KW_JITTA) {
                    last.posEnd = _currPos;
                    last.type = TOKENTYPE::GTE_LTE_PREFIX;
                    break;
                }
            }

            goto defaultCase;
        }

        case TOKENTYPE::KW_PHIR: {
            if (res.tokens.empty()) break;

            Token &last = res.tokens.back();
            if (last.type != TOKENTYPE::KW_YA) break;

            // ya phir
            last.type = kwType;
            last.posEnd = _currPos;
            break;
        }

        case TOKENTYPE::KW_THO: {
            if (!res.tokens.empty()) {
                // nahi tho
                if (Token &last = res.tokens.back(); last.type == TOKENTYPE::KW_NAHI) {
                    last.posEnd = _currPos;
                    last.type = TOKENTYPE::ELSE;
                    break;
                }
            }

            goto defaultCase;
        }

        case TOKENTYPE::KW_HAI:
        case TOKENTYPE::KW_NAHI: {
            if (!res.tokens.empty()) {
                // Expr1 Expr2 jitta hai, Expr1 Expr2 jitta nahi hai
                if (Token &last = res.tokens.back(); last.type == TOKENTYPE::KW_JITTA) {
                    last.posEnd = _currPos;
                    last.type = TOKENTYPE::KW_BARAABAR;
                }
            }

            goto defaultCase;
        }

        case TOKENTYPE::KW_BADA:
        case TOKENTYPE::KW_CHOTA: {
            switch (Token &last = res.tokens.back(); last.type) {
                // Expr1 Expr2 se bada | chota
                case TOKENTYPE::KW_SE: {
                    last.type = kwType;
                    last.posEnd = _currPos;
                    break;
                }

                // Expr1 Expr2 jitta bada | chota
                case TOKENTYPE::KW_JITTA: {
                    last.posEnd = _currPos;
                    last.type = TOKENTYPE::KW_BARAABAR;
                    break;
                }

                // Expr1 Expr2 jitta ya bada | chota
                case TOKENTYPE::GTE_LTE_PREFIX: {
                    last.posEnd = _currPos;
                    last.type = kwType == TOKENTYPE::KW_BADA ? TOKENTYPE::GTE : TOKENTYPE::LTE;
                    break;
                }

                default: break;
            }

            break;
        }

    defaultCase:
        default:
            res.tokens.emplace_back(kwType, startPos, _currPos);
    }
}

void Lexer::_genKeywordOrVarToken(LexerResult &res) {
    ParsePosition startPos = _currPos;

    while (true) {
        char chr = _currChar();
        if (!(isalnum(chr) || chr == '_')) break;
        _currPos++;
    }

    auto text = std::string(_srcCode.substr(startPos.index, _currPos.index - startPos.index));

    if (auto it = KEYWORD.find(text); it != KEYWORD.end()) {
        if (TOKENTYPE &type = it->second; type != TOKENTYPE::BOOL)
            _genKeywordToken(startPos, type, res);
        else
            res.tokens.emplace_back(type, text == "sahi", startPos, _currPos);

        return;
    }

    res.tokens.emplace_back(TOKENTYPE::VAR, text, startPos, _currPos);
}


void Lexer::_getNextToken(LexerResult &res) {
start:
    char chr = _currChar();

    if (chr == '\0') res.tokens.emplace_back(TOKENTYPE::EOF_, _currPos);

    else if (chr == ' ' || chr == '\t' || chr == '\n') {
        chr == '\n' ? _currPos.nextLine() : _currPos++;
        goto start;
    }

    else if (isdigit(chr)) _genNumberToken(res);

    else if (isalpha(chr) || chr == '_') _genKeywordOrVarToken(res);

    else {
        ParsePosition posStart = _currPos;
        _currPos++;

        switch (chr) {
            case '+': res.tokens.emplace_back(TOKENTYPE::PLUS, posStart); break;
            case '-': res.tokens.emplace_back(TOKENTYPE::MINUS, posStart); break;
            case '*': res.tokens.emplace_back(TOKENTYPE::STAR, posStart); break;
            case '^': res.tokens.emplace_back(TOKENTYPE::POW, posStart); break;
            case '%': res.tokens.emplace_back(TOKENTYPE::MOD, posStart); break;

            case '/': {
                TOKENTYPE type = TOKENTYPE::DIV_D;
                if (_currChar() == '/') {
                    _currPos++;
                    type = TOKENTYPE::DIV_I;
                }

                res.tokens.emplace_back(type, posStart);
                break;
            }

            case '(': res.tokens.emplace_back(TOKENTYPE::LPAREN, posStart); break;
            case ')': res.tokens.emplace_back(TOKENTYPE::RPAREN, posStart); break;
            case ',': res.tokens.emplace_back(TOKENTYPE::COMMA, posStart); break;

            default:
                res.error.emplace(ErrorMsg::UNEXPECTED_CHAR(chr), Token(posStart));
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
