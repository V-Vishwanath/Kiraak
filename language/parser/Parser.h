
#ifndef KIRAAK_PARSER_H
#define KIRAAK_PARSER_H


#include "../lexer/Lexer.h"
#include "../ast_nodes/ASTNodes.h"
#include "../utils/ResultWrappers.h"


class Parser {
    std::vector<Token>& _tokens;
    const Token* _currToken{};

    void _parseNext();

    enum PARSETYPE {
        POWER, FACTOR, MODULO, TERM, ARITHMETIC, COMPARISON, CONJUNCTION
    };

    static bool _isComparisonPossible(const Token &token);
    static bool _compareOpToken(const Token&, const PARSETYPE&);

    // Math Parsing
    void _parseLiteral(ResultAST&);
    void _parsePower(ResultAST&);
    void _parseFactor(ResultAST&);
    void _parseModulo(ResultAST&);
    void _parseTerm(ResultAST&);
    void _parseArithmetic(ResultAST&);
    void _parseComparison(ResultAST&);
    void _parseConjunction(ResultAST&);
    void _parseExpression(ResultAST&);

    void _parseBinaryExpr(const PARSETYPE&, ResultAST&);

    // Variables
    void _parseVariableAssignment(ResultAST&);
    void _parseVariableDeclaration(ResultAST&);
    void _parseVariable(ResultAST&);

    // Comparisons
    void _parseComparisonTree(std::shared_ptr<ASTNode>&, ResultAST&);

    // Conditionals
    void _parseConditional(ResultAST&);


public:
    explicit Parser(std::vector<Token>& tokens): _tokens(tokens) {
        _parseNext();
    }

    ResultAST genAST() {
        ResultAST res;
        _parseExpression(res);

        remTokensCheck:
        if (_currToken->type != TOKENTYPE::EOF_ && !res.error.has_value()) {
            if (_currToken->type == TOKENTYPE::KW_HAI) {
                _parseNext();
                goto remTokensCheck;
            }

            res.error.emplace(InvalidSyntaxError(ErrorMsg::EXPECTED_MATH_OPERATOR, *_currToken));
        }

        return res;
    }
};


#endif //KIRAAK_PARSER_H
