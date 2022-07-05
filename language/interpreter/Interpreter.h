
#ifndef KIRAAK_INTERPRETER_H
#define KIRAAK_INTERPRETER_H


#include "../utils/Utils.h"
#include "../parser/Parser.h"
#include "../context/Context.h"
#include "../datatypes/DataTypes.h"
#include "../utils/ResultWrappers.h"


class Interpreter {
    static void _processLiteralNode(LiteralNode*, ASTParseResult&, Context&);
    void _processUnaryExprNode(UnaryExprNode*, ASTParseResult&, Context&);
    void _processBinaryExprNode(BinaryExprNode*, ASTParseResult&, Context&);

    void _processVarAssignNode(VarAssignNode*, ASTParseResult&, Context&);
    static void _processVarAccessNode(VarAccessNode*, ASTParseResult&, Context&);

    void _processNode(ASTNode *rootNode,ASTParseResult &res, Context &ctx);

public:
    ASTParseResult parseAST(ASTNode *rootNode, Context& ctx) {
        ASTParseResult res;
        _processNode(rootNode, res, ctx);
        return res;
    }
};


#endif //KIRAAK_INTERPRETER_H
