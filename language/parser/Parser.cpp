#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"

#include "Parser.h"


void Parser::_parseNext() {
    if (_currToken == nullptr)
        _currToken = &_tokens[0];

    else if (_currToken->type != TOKENTYPE::EOF_)
        _currToken += 1;
}


bool Parser::_isComparisonPossible(const Token &token) {
    switch (token.type) {
        case TOKENTYPE::VAR:
        case TOKENTYPE::NONE:

        case TOKENTYPE::INT:
        case TOKENTYPE::BOOL:
        case TOKENTYPE::DOUBLE:

        case TOKENTYPE::LPAREN: return true;

        default: return false;
    }
}


bool Parser::_compareOpToken(const Token& token, const PARSETYPE& parsetype) {
    switch (parsetype) {
        case PARSETYPE::POWER:
        case PARSETYPE::FACTOR:
            return token.type == TOKENTYPE::POW;

        case PARSETYPE::MODULO:
            return token.type == TOKENTYPE::MOD;

        case PARSETYPE::TERM:
            return token.type == TOKENTYPE::STAR || token.type == TOKENTYPE::DIV_I || token.type == TOKENTYPE::DIV_D;

        case PARSETYPE::ARITHMETIC:
            return token.type == TOKENTYPE::PLUS || token.type == TOKENTYPE::MINUS;

        case PARSETYPE::COMPARISON:
            return token.type == TOKENTYPE::KW_BARAABAR ||
                token.type == TOKENTYPE::KW_BADA || token.type == TOKENTYPE::GTE ||
                token.type == TOKENTYPE::KW_CHOTA || token.type == TOKENTYPE::LTE;

        case PARSETYPE::CONJUNCTION:
            return token.type == TOKENTYPE::KW_AUR || token.type == TOKENTYPE::KW_YA;

        default: return false;
    }
}


void Parser::_parseConditional(ResultAST &res) {
    std::shared_ptr<ASTNode> defaultCase;
    std::vector<ConditionalPair> casePairs;

start:
    _parseNext();

    _parseExpression(res);
    if (res.error.has_value()) return;
    auto caseCondition = res.rootNode;

    if (_currToken->type == TOKENTYPE::KW_HAI) _parseNext();

    if (_currToken->type != TOKENTYPE::KW_THO) {
        res.error.emplace(ErrorMsg::EXPECTED_THO, *_currToken);
        return;
    }

    _parseNext();

    _parseExpression(res);
    if (res.error.has_value()) return;
    auto caseExpression = res.rootNode;

    casePairs.emplace_back(caseCondition, caseExpression);

    if (_currToken->type == TOKENTYPE::KW_PHIR) goto start;
    else if (_currToken->type == TOKENTYPE::ELSE) {
        _parseNext();

        _parseExpression(res);
        if (res.error.has_value()) return;
        defaultCase = res.rootNode;
    }

    res.rootNode = std::make_shared<ConditionalNode>(casePairs, defaultCase);
}

void Parser::_parseLiteral(ResultAST &res) {
    switch (_currToken->type) {
        case TOKENTYPE::LPAREN: {
            _parseNext();

            _parseExpression(res);
            if (res.error.has_value()) return;

            if (_currToken->type == TOKENTYPE::RPAREN) _parseNext();
            else res.error.emplace(ErrorMsg::EXPECTED_RPAREN, *_currToken);
            break;
        }

        case TOKENTYPE::NONE:
        case TOKENTYPE::INT:
        case TOKENTYPE::BOOL:
        case TOKENTYPE::DOUBLE: {
            res.rootNode = std::make_shared<LiteralNode>(*_currToken);
            _parseNext();
            break;
        }

        case TOKENTYPE::VAR: {
            res.rootNode = std::make_shared<VarAccessNode>(*_currToken);
            _parseNext();
            break;
        }

        case TOKENTYPE::KW_AGAR: {
            _parseConditional(res);
            break;
        }

        default:
            res.error.emplace(ErrorMsg::EXPECTED_NUMBER, *_currToken);
    }
}


void Parser::_parsePower(ResultAST &res) {
    _parseBinaryExpr(PARSETYPE::POWER, res);
}

void Parser::_parseFactor(ResultAST &res) {
    TOKENTYPE tokentype = _currToken->type;
    if (tokentype == TOKENTYPE::PLUS || tokentype == TOKENTYPE::MINUS) {
        Token opToken = *_currToken;

        _parseNext();
        _parseLiteral(res);

        if (res.error.has_value()) return;
        res.rootNode = std::make_shared<UnaryExprNode>(opToken, res.rootNode);
    }

    else _parsePower(res);
}


void Parser::_parseModulo(ResultAST &res) {
    _parseBinaryExpr(PARSETYPE::FACTOR, res);
}

void Parser::_parseTerm(ResultAST &res) {
    _parseBinaryExpr(PARSETYPE::MODULO, res);
}

void Parser::_parseArithmetic(ResultAST &res) {
    _parseBinaryExpr(PARSETYPE::TERM, res);
}

void Parser::_parseComparison(ResultAST &res) {
    _parseBinaryExpr(PARSETYPE::ARITHMETIC, res);
}

void Parser::_parseConjunction(ResultAST &res) {
    _parseBinaryExpr(PARSETYPE::COMPARISON, res);
}


void Parser::_parseVariableAssignment(ResultAST &res) {
    Token varToken = *_currToken;
    _parseNext();

    _parseNext();

    _parseExpression(res);
    if (res.error.has_value()) return;

    res.rootNode = std::make_shared<VarAssignNode>(varToken, res.rootNode);
}

void Parser::_parseVariableDeclaration(ResultAST &res) {
    std::vector<Token> variables;

    variables.emplace_back(*_currToken);
    _parseNext();

    while (_currToken ->type == TOKENTYPE::COMMA) {
        _parseNext();
        if (_currToken->type != TOKENTYPE::VAR) {
            res.error.emplace(ErrorMsg::EXPECTED_VAR_NAME, *_currToken);
            return;
        }

        variables.emplace_back(*_currToken);
        _parseNext();
    }

    auto declareStart = _currToken->posStart;

    if (_currToken->type != TOKENTYPE::KW_BANAKE) {
        res.error.emplace(ErrorMsg::EXPECTED_BANAKE, *_currToken);
        return;
    }

    _parseNext();
    if (_currToken->type != TOKENTYPE::KW_RAKH) {
        res.error.emplace(ErrorMsg::EXPECTED_RAKH, *_currToken);
        return;
    }

    auto declareEnd = _currToken->posEnd;
    _parseNext();

    Token nullToken(TOKENTYPE::NONE, declareStart, declareEnd);

    res.rootNode = std::make_shared<LiteralNode>(nullToken);
    res.rootNode = std::make_shared<VarAssignNode>(variables[0], res.rootNode);

    for (int i = 1; i < variables.size(); i++)
        res.rootNode = std::make_shared<VarAssignNode>(variables[i], res.rootNode);
}

void Parser::_parseVariable(ResultAST &res) {
    switch ((_currToken + 1)->type) {
        case TOKENTYPE::KW_BOLETHO: {
            _parseVariableAssignment(res);
            return;
        }

        case TOKENTYPE::COMMA:
        case TOKENTYPE::KW_BANAKE: {
            _parseVariableDeclaration(res);
            return;
        }

        default: {
            _parseBinaryExpr(PARSETYPE::CONJUNCTION, res);
            return;
        }
    }
}


void Parser::_parseExpression(ResultAST &res) {
    if (_currToken->type == TOKENTYPE::VAR) _parseVariable(res);
    else _parseBinaryExpr(PARSETYPE::CONJUNCTION, res);
}


void Parser::_parseComparisonTree(std::shared_ptr<ASTNode> &left, ResultAST &res) {
start:
    if (_currToken->type == TOKENTYPE::KW_NAHI) {
        Token notToken = *_currToken;

        _parseNext();
        if (_currToken->type != TOKENTYPE::KW_HAI) {
            res.error.emplace(ErrorMsg::EXPECTED_HAI, *_currToken);
            return;
        }

        notToken.posEnd = _currToken->posEnd;

        _parseNext();
        left = std::make_shared<UnaryExprNode>(notToken, left);
        return;
    }

    if (_isComparisonPossible(*_currToken)) {
        _parseComparison(res);
        if (res.error.has_value()) return;

        auto right = res.rootNode;

        if (right->Type() == ASTNode::TYPE::LITERAL) {
            TOKENTYPE currType = _currToken->type;
            auto &node = *dynamic_cast<LiteralNode*>(right.get());

            if (currType == TOKENTYPE::KW_HAI) {
                Token eqToken(TOKENTYPE::KW_BARAABAR, node.token.posStart, _currToken->posEnd);
                left = std::make_shared<BinaryExprNode>(left, eqToken, right);

                _parseNext();
                goto start;
            }

            else if (currType == TOKENTYPE::KW_NAHI) {
                Token neToken(TOKENTYPE::NE, node.token.posStart, _currToken->posEnd);

                _parseNext();
                if (_currToken->type != TOKENTYPE::KW_HAI) {
                    res.error.emplace(ErrorMsg::EXPECTED_HAI, *_currToken);
                    return;
                }

                neToken.posEnd = _currToken->posEnd;

                _parseNext();
                left = std::make_shared<BinaryExprNode>(left, neToken, right);
                goto start;
            }
        }

        if (!_compareOpToken(*_currToken, PARSETYPE::COMPARISON)) {
            res.error.emplace("INCORRECT COMPARISION", *_currToken);
            return;
        }

        left = std::make_shared<BinaryExprNode>(left, *_currToken, right);

        _parseNext();
        if (_currToken->type == TOKENTYPE::KW_NAHI) {
            left = std::make_shared<UnaryExprNode>(*_currToken, left);
            _parseNext();
        }

        if (_currToken->type != TOKENTYPE::KW_HAI) {
            res.error.emplace(ErrorMsg::EXPECTED_HAI, *_currToken);
            return;
        }

        _parseNext();
        goto start;
    }
}


void Parser::_parseBinaryExpr(const Parser::PARSETYPE &parsetype, ResultAST &res) {
    void (Parser::*extractExpr)(ResultAST&);
    switch (parsetype) {
        case PARSETYPE::POWER:
        case PARSETYPE::FACTOR: {
            extractExpr = &Parser::_parseFactor;
            break;
        }

        case PARSETYPE::MODULO: {
            extractExpr = &Parser::_parseModulo;
            break;
        }

        case PARSETYPE::TERM: {
            extractExpr = &Parser::_parseTerm;
            break;
        }

        case PARSETYPE::ARITHMETIC: {
            extractExpr = &Parser::_parseArithmetic;
            break;
        }

        case PARSETYPE::COMPARISON: {
            extractExpr = &Parser::_parseComparison;
            break;
        }

        case PARSETYPE::CONJUNCTION: {
            extractExpr = &Parser::_parseConjunction;
        }
    }

    parsetype == PARSETYPE::POWER ? _parseLiteral(res) : (this->*extractExpr)(res);
    if (res.error.has_value()) return;

    auto left = res.rootNode;

    if (parsetype == PARSETYPE::COMPARISON) _parseComparisonTree(left, res);
    else {
        while (_compareOpToken(*_currToken, parsetype)) {
            Token opToken = *_currToken;

            _parseNext();

            (this->*extractExpr)(res);
            if (res.error.has_value()) return;

            auto right = res.rootNode;
            left = std::make_shared<BinaryExprNode>(left, opToken, right);
        }
    }

    res.rootNode = left;
}

#pragma clang diagnostic pop