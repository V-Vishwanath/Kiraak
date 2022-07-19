#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"

#include "Interpreter.h"


void Interpreter::_parseData(DATATYPE &value, ASTParseResult &res, Context &ctx) {
    switch (DataType *dataPtr = res.data.get(); dataPtr->Type()) {
        case DataType::TYPE::NONE: {
            value.emplace<None>(*dynamic_cast<None*>(dataPtr));
            return;
        }

        case DataType::TYPE::NUMBER: {
            value.emplace<Number>(*dynamic_cast<Number*>(dataPtr));
            return;
        }

        case DataType::TYPE::BOOLEAN: {
            value.emplace<Boolean>(*dynamic_cast<Boolean*>(dataPtr));
            return;
        }

        default:
            return;
    }
}


void Interpreter::_processLiteralNode(LiteralNode *node, ASTParseResult &res, Context &ctx) {
    Token &token = node->token;

    if (!token.value.has_value()) {
        res.data = std::make_shared<None>(token.posStart, token.posEnd);
        return;
    }

    std::visit(VariantVisit {
        [&res, &token](bool &value) {
            res.data = std::make_shared<Boolean>(value, token.posStart, token.posEnd);
        },

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

    if (opToken.type == TOKENTYPE::PLUS || opToken.type == TOKENTYPE::MINUS) {
        if (res.data->Type() != DataType::TYPE::NUMBER) {
            Token errToken = Token(opToken.posStart, opToken.posEnd);
            res.error.emplace(RuntimeError(ErrorMsg::SIGNED_NON_NUMBER, errToken, ctx));
            return;
        }

        if (opToken.type == TOKENTYPE::MINUS)
            res.data = -(*dynamic_cast<Number*>(res.data.get()));
    }

    else if (opToken.type == TOKENTYPE::KW_NAHI) {
        if (res.data->Type() != DataType::TYPE::BOOLEAN) {
            Token errToken = Token(opToken.posStart, opToken.posEnd);
            res.error.emplace(RuntimeError(ErrorMsg::NON_BOOLEAN_INVERSION, errToken, ctx));
            return;
        }

        res.data = !(*dynamic_cast<Boolean*>(res.data.get()));
    }
}

void Interpreter::_processBinaryExprNode(BinaryExprNode *node, ASTParseResult &res, Context &ctx) {
    Token &opToken = node->opToken;

    _processNode((node->left).get(), res, ctx);
    if (res.error.has_value()) return;

    DATATYPE left;
    _parseData(left, res, ctx);
    if (res.error.has_value()) return;

    _processNode((node->right).get(), res, ctx);
    if (res.error.has_value()) return;

    DATATYPE right;
    _parseData(right, res, ctx);
    if (res.error.has_value()) return;

    std::visit(VariantVisit {
        [&opToken, &res, &ctx](Number &left, Number &right) {
            switch (opToken.type) {
                case TOKENTYPE::PLUS: res.data = left + right; break;
                case TOKENTYPE::MINUS: res.data = left - right; break;
                case TOKENTYPE::STAR: res.data = left * right; break;
                case TOKENTYPE::POW: res.data = left ^ right; break;
                case TOKENTYPE::MOD: res.data = left % right; break;

                case TOKENTYPE::DIV_I:
                case TOKENTYPE::DIV_D: {
                    res.data = opToken.type == TOKENTYPE::DIV_D ? left / right : left.divideAsInt(right);
                    if (res.data == nullptr)
                        res.error.emplace(RuntimeError(ErrorMsg::DIVISION_BY_ZERO, right.getErrToken(), ctx));

                    break;
                }

                case TOKENTYPE::KW_BARAABAR: res.data = left == right; break;
                case TOKENTYPE::KW_CHOTA: res.data = left < right; break;
                case TOKENTYPE::KW_BADA: res.data = left > right; break;
                case TOKENTYPE::LTE: res.data = left <= right; break;
                case TOKENTYPE::GTE: res.data = left >= right; break;
                case TOKENTYPE::NE: res.data = left != right; break;

                default:
                    res.error.emplace(
                        ErrorMsg::UNDEFINED_BIN_OP_NUM(opToken.posStart.index, opToken.posEnd.index),
                        opToken, ctx
                    );
            }
        },

        [&opToken, &res, &ctx] (Boolean &left, Boolean &right) {
            switch (opToken.type) {
                case TOKENTYPE::NE: res.data = left != right; break;
                case TOKENTYPE::KW_BARAABAR: res.data = left == right; break;

                case TOKENTYPE::KW_AUR: res.data = left && right; break;
                case TOKENTYPE::KW_YA: res.data = left || right; break;

                default:
                    res.error.emplace(
                        ErrorMsg::UNDEFINED_BIN_OP_BOOL(opToken.posStart.index, opToken.posEnd.index),
                        opToken, ctx
                    );
            }
        },

        [&opToken, &res, &ctx] (auto &left, auto &right) {
            if (left.Type() == DataType::TYPE::NONE || right.Type() == DataType::TYPE::NONE) {
                if (opToken.type == TOKENTYPE::KW_BARAABAR || opToken.type == TOKENTYPE::NE) {
                    res.data = std::make_shared<Boolean>(
                        opToken.type == TOKENTYPE::NE ? left.Type() != right.Type() : left.Type() == right.Type(),
                        opToken.posStart, opToken.posEnd
                    );

                    return;
                }
            }

            res.error.emplace(ErrorMsg::INVALID_BIN_OP, opToken, ctx);
        }

    }, left, right);
}


void Interpreter::_processVarAssignNode(VarAssignNode *node, ASTParseResult &res, Context &ctx) {
    TokenValue value = (node->varToken).value.value();

    _processNode((node->value).get(), res, ctx);
    if (res.error.has_value()) return;

    ctx.symbolTable.set(std::get<std::string>(value), res.data);
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


void Interpreter::_processConditionalNode(ConditionalNode *node, ASTParseResult &res, Context &ctx) {
    for (auto &[condRoot, exprRoot]: node->casePairs) {
        _processNode(condRoot.get(), res, ctx);
        if (res.error.has_value()) return;

        if (res.data->Type() != DataType::TYPE::BOOLEAN) {
            res.error.emplace(ErrorMsg::NON_BOOLEAN_COMP, res.data->getErrToken(), ctx);
            return;
        }

        if (*dynamic_cast<Boolean*>(res.data.get())) {
            _processNode(exprRoot.get(), res, ctx);
            return;
        }
    }

    if (node->defaultCase != nullptr) {
        _processNode(node->defaultCase.get(), res, ctx);
        return;
    }

    res.data = std::make_shared<None>();
}


void Interpreter::_processNode(ASTNode *rootNode, ASTParseResult &res, Context &ctx) {
    switch (rootNode->Type()) {
        case ASTNode::TYPE::LITERAL:
            return _processLiteralNode(dynamic_cast<LiteralNode*>(rootNode), res, ctx);

        case ASTNode::TYPE::UNARY_EXPR:
            return _processUnaryExprNode(dynamic_cast<UnaryExprNode*>(rootNode), res, ctx);

        case ASTNode::TYPE::BINARY_EXPR:
            return _processBinaryExprNode(dynamic_cast<BinaryExprNode*>(rootNode), res, ctx);


        case ASTNode::TYPE::VAR_ASSIGNMENT:
            return _processVarAssignNode(dynamic_cast<VarAssignNode*>(rootNode), res, ctx);

        case ASTNode::TYPE::VAR_ACCESS:
            return _processVarAccessNode(dynamic_cast<VarAccessNode*>(rootNode), res, ctx);


        case ASTNode::TYPE::CONDITIONAL:
            return _processConditionalNode(dynamic_cast<ConditionalNode*>(rootNode), res, ctx);
    }
}

#pragma clang diagnostic pop