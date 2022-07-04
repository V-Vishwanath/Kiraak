
#ifndef KIRAAK_INTERPRETER_H
#define KIRAAK_INTERPRETER_H


#include "../parser/Parser.h"
#include "../context/Context.h"
#include "../utils/ResultWrappers.h"


class Interpreter {
    static void _processLiteralNode(LiteralNode*, ASTParseResult&, const Context&);
    void _processUnaryExprNode(UnaryExprNode*, ASTParseResult&, const Context&);
    void _processBinaryExprNode(BinaryExprNode*, ASTParseResult&, const Context&);

    void _processNode(ASTNode *rootNode,ASTParseResult &res, const Context &ctx);

public:
    ASTParseResult parseAST(ASTNode *rootNode, const Context& ctx) {
        ASTParseResult res;
        _processNode(rootNode, res, ctx);
        return res;
    }
};


#endif //KIRAAK_INTERPRETER_H
