
#ifndef KIRAAK_PARSER_H
#define KIRAAK_PARSER_H


#include "../lexer/Lexer.h"
#include "../utils/ResultWrappers.h"


class Parser {
    std::vector<Token>& _tokens;
    const Token* _currToken{};

    void _parseNext();

    enum PARSETYPE {
        POWER, MODULO, TERM, EXPRESSION
    };

    static bool _compareOpToken(const TOKENTYPE &tokentype, const PARSETYPE &parsetype);

    // Math Parsing
    void _parseLiteral(ResultAST&);
    void _parsePower(ResultAST&);
    void _parseFactor(ResultAST&);
    void _parseModulo(ResultAST&);
    void _parseTerm(ResultAST&);
    void _parseExpression(ResultAST&);

    void _parseBinaryExpr(const PARSETYPE&, ResultAST&);


public:
    explicit Parser(std::vector<Token>& tokens): _tokens(tokens) {
        _parseNext();
    }

    ResultAST genAST() {
        ResultAST res;
        _parseExpression(res);

        if (!res.error.has_value() && _currToken->type != TOKENTYPE::EOF_)
            res.error.emplace(InvalidSyntaxError(ErrorMsg::EXPECTED_MATH_OPERATOR, *_currToken));

        return res;
    }
};


#endif //KIRAAK_PARSER_H
