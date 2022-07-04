#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"

#include "Parser.h"


void Parser::_parseNext() {
    if (_currToken == nullptr)
        _currToken = &_tokens[0];

    else if (_currToken->type != TOKENTYPE::EOF_)
        _currToken += 1;
}


bool Parser::_compareOpToken(const TOKENTYPE& tokentype, const PARSETYPE& parsetype) {
    switch (parsetype) {
        case PARSETYPE::POWER: return tokentype == TOKENTYPE::POW;
        case PARSETYPE::MODULO: return tokentype == TOKENTYPE::MOD;
        case PARSETYPE::TERM: return tokentype == TOKENTYPE::MUL || tokentype == TOKENTYPE::DIV;
        case PARSETYPE::EXPRESSION: return tokentype == TOKENTYPE::ADD || tokentype == TOKENTYPE::SUB;
        default: return false;
    }
}


void Parser::_parseLiteral(ResultAST &res) {
    switch (_currToken->type) {
        case TOKENTYPE::LPAREN: {
            _parseNext();

            _parseExpression(res);
            if (res.error.has_value()) return;

            if (_currToken->type == TOKENTYPE::RPAREN) _parseNext();
            else res.error.emplace(InvalidSyntaxError(ErrorMsg::EXPECTED_RPAREN, *_currToken));
            break;
        }

        case TOKENTYPE::INT:
        case TOKENTYPE::DOUBLE: {
            res.rootNode = std::make_shared<LiteralNode>(*_currToken);
            _parseNext();
            break;
        }

        default:
            res.error.emplace(InvalidSyntaxError(ErrorMsg::EXPECTED_NUMBER, *_currToken));
    }
}


void Parser::_parsePower(ResultAST &res) {
    _parseBinaryExpr(PARSETYPE::POWER, res);
}

void Parser::_parseFactor(ResultAST &res) {
    TOKENTYPE tokentype = _currToken->type;
    if (tokentype == TOKENTYPE::ADD || tokentype == TOKENTYPE::SUB) {
        Token opToken = *_currToken;

        _parseNext();
        _parseLiteral(res);

        if (res.error.has_value()) return;
        res.rootNode = std::make_shared<UnaryExprNode>(opToken, res.rootNode);
    }

    else _parsePower(res);
}

void Parser::_parseModulo(ResultAST &res) {
    _parseBinaryExpr(PARSETYPE::MODULO, res);
}

void Parser::_parseTerm(ResultAST &res) {
    _parseBinaryExpr(PARSETYPE::TERM, res);
}

void Parser::_parseExpression(ResultAST &res) {
    _parseBinaryExpr(PARSETYPE::EXPRESSION, res);
}


void Parser::_parseBinaryExpr(const Parser::PARSETYPE &parsetype, ResultAST &res) {
    void (Parser::*extractExpr)(ResultAST&);
    switch (parsetype) {
        case PARSETYPE::POWER:
        case PARSETYPE::MODULO: {
            extractExpr = &Parser::_parseFactor;
            break;
        }

        case PARSETYPE::TERM: {
            extractExpr = &Parser::_parseModulo;
            break;
        }

        case PARSETYPE::EXPRESSION: {
            extractExpr = &Parser::_parseTerm;
            break;
        }
    }

    parsetype == PARSETYPE::POWER ? _parseLiteral(res) : (this->*extractExpr)(res);
    if (res.error.has_value()) return;

    auto left = res.rootNode;
    while (_compareOpToken(_currToken->type, parsetype)) {
        Token opToken = *_currToken;

        _parseNext();

        (this->*extractExpr)(res);
        if (res.error.has_value()) return;

        auto right = res.rootNode;
        left = std::make_shared<BinaryExprNode>(left, opToken, right);
    }

    res.rootNode = left;
}

#pragma clang diagnostic pop