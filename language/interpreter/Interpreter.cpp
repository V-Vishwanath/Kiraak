#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"

#include "Interpreter.h"


void Interpreter::_processLiteralNode(LiteralNode *node, ASTParseResult &res, Context &ctx) {
    Token &token = node->token;

    std::visit(VariantVisit {
        [&res, &token](int &value) {
            res.data = std::make_shared<Number>(value, token.posStart, token.posEnd);
        },

        [&res, &token](double &value) {
            res.data = std::make_shared<Number>(value, token.posStart, token.posEnd);
        },

        [](auto &value) {

        },
    }, token.value.value());
}


void Interpreter::_processUnaryExprNode(UnaryExprNode *node, ASTParseResult &res, Context &ctx) {
    _processNode(node->exprNode.get(), res, ctx);
    if (res.error.has_value()) return;

    Token &opToken = node->opToken;
    auto num = *dynamic_cast<Number*>(res.data.get());
    if (opToken.type == TOKENTYPE::SUB)
        res.data = num * Number(-1, opToken.posStart, opToken.posEnd);
}


void Interpreter::_processBinaryExprNode(BinaryExprNode *node, ASTParseResult &res, Context &ctx) {
    _processNode((node->left).get(), res, ctx);
    if (res.error.has_value()) return;
    auto left = *dynamic_cast<Number*>(res.data.get());

    _processNode((node->right).get(), res, ctx);
    if (res.error.has_value()) return;
    auto right = *dynamic_cast<Number*>(res.data.get());

    switch ((node->opToken).type) {
        case TOKENTYPE::ADD: res.data = left + right; break;
        case TOKENTYPE::SUB: res.data = left - right; break;
        case TOKENTYPE::MUL: res.data = left * right; break;
        case TOKENTYPE::POW: res.data = left ^ right; break;
        case TOKENTYPE::MOD: res.data = left % right; break;

        case TOKENTYPE::DIV: {
            res.data = left / right;
            if (res.data == nullptr)
                res.error.emplace(RuntimeError(ErrorMsg::DIVISION_BY_ZERO, right.getErrToken(), ctx));

            break;
        }

        default: break;
    }
}


void Interpreter::_processVarAccessNode(VarAccessNode *node, ASTParseResult &res, Context &ctx) {
    Token &token = node->varToken;
    auto varname = std::get<std::string>(token.value.value());

    res.data = ctx.symbolTable.get(varname);

    if (res.data == nullptr) {
        res.error.emplace(RuntimeError(ErrorMsg::VAR_NOT_DEFINED(varname), node->varToken, ctx));
        return;
    }

    res.data->setPos(token.posStart, token.posEnd);
}


void Interpreter::_processVarAssignNode(VarAssignNode *node, ASTParseResult &res, Context &ctx) {
    TokenValue value = (node->varToken).value.value();

    _processNode((node->value).get(), res, ctx);
    if (res.error.has_value()) return;

    ctx.symbolTable.set(std::get<std::string>(value), res.data);
}


void Interpreter::_processNode(ASTNode *rootNode, ASTParseResult &res, Context &ctx) {
    if (auto node = dynamic_cast<LiteralNode*>(rootNode)) return _processLiteralNode(node, res, ctx);
    if (auto node = dynamic_cast<UnaryExprNode*>(rootNode)) return _processUnaryExprNode(node, res, ctx);
    if (auto node = dynamic_cast<BinaryExprNode*>(rootNode)) return _processBinaryExprNode(node, res, ctx);

    if (auto node = dynamic_cast<VarAssignNode*>(rootNode)) return _processVarAssignNode(node, res, ctx);
    if (auto node = dynamic_cast<VarAccessNode*>(rootNode)) return _processVarAccessNode(node, res, ctx);
}

#pragma clang diagnostic pop