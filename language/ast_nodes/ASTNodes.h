
#ifndef KIRAAK_ASTNODES_H
#define KIRAAK_ASTNODES_H


#include "_ASTNode.h"
#include "../token/Token.h"
#include "../errors/Errors.h"

#include <sstream>
#include <utility>
#include <memory>


struct LiteralNode: ASTNode {
    Token token;

    TYPE Type() override { return ASTNode::TYPE::LITERAL; }
    explicit LiteralNode(Token token):
        token(std::move(token)) {}
};


struct UnaryExprNode: ASTNode {
    Token opToken;
    std::shared_ptr<ASTNode> exprNode;

    TYPE Type() override { return ASTNode::TYPE::UNARY_EXPR; }
    UnaryExprNode(Token opToken, std::shared_ptr<ASTNode> &node):
        opToken(std::move(opToken)), exprNode(node) {}
};


struct BinaryExprNode: ASTNode {
    Token opToken;
    std::shared_ptr<ASTNode> left, right;

    TYPE Type() override { return ASTNode::TYPE::BINARY_EXPR; }
    BinaryExprNode(std::shared_ptr<ASTNode> &left, Token opToken, std::shared_ptr<ASTNode> &right):
        left(left), opToken(std::move(opToken)), right(right) {}
};


struct VarAccessNode: ASTNode {
    Token varToken;

    TYPE Type() override { return ASTNode::TYPE::VAR_ACCESS; }
    explicit VarAccessNode(Token varToken):
        varToken(std::move(varToken)) {}
};


struct VarAssignNode: ASTNode {
    Token varToken;
    std::shared_ptr<ASTNode> value;

    TYPE Type() override { return ASTNode::TYPE::VAR_ASSIGNMENT; }
    VarAssignNode(Token varToken, std::shared_ptr<ASTNode> &value):
        varToken(std::move(varToken)), value(value) {}
};


using ConditionalPair = std::pair<std::shared_ptr<ASTNode>, std::shared_ptr<ASTNode>>;
struct ConditionalNode: ASTNode {
    std::shared_ptr<ASTNode> defaultCase;
    std::vector<ConditionalPair> casePairs;

    TYPE Type() override { return ASTNode::TYPE::CONDITIONAL; }
    ConditionalNode(std::vector<ConditionalPair> casePairs, std::shared_ptr<ASTNode> defaultCase):
        casePairs(std::move(casePairs)), defaultCase(std::move(defaultCase)) {}
};

#endif //KIRAAK_ASTNODES_H
