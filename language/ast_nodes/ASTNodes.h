
#ifndef KIRAAK_ASTNODES_H
#define KIRAAK_ASTNODES_H


#include "ASTNode.h"
#include "../token/Token.h"
#include "../errors/Errors.h"

#include <sstream>
#include <utility>
#include <memory>


struct LiteralNode: ASTNode {
    Token token;

    [[nodiscard]] std::string toString() const override;
    explicit LiteralNode(Token token): token(std::move(token)) {}
};


struct UnaryExprNode: ASTNode {
    Token opToken;
    std::shared_ptr<ASTNode> exprNode;

    [[nodiscard]] std::string toString() const override;
    UnaryExprNode(Token opToken, std::shared_ptr<ASTNode> &node): opToken(std::move(opToken)), exprNode(node) {}
};


struct BinaryExprNode: ASTNode {
    Token opToken;
    std::shared_ptr<ASTNode> left, right;

    [[nodiscard]] std::string toString() const override;
    BinaryExprNode(std::shared_ptr<ASTNode> &left, Token opToken, std::shared_ptr<ASTNode> &right):
        left(left), opToken(std::move(opToken)), right(right) {}
};


struct VarAssignNode: ASTNode {
    Token varToken;
    std::shared_ptr<ASTNode> value;

    [[nodiscard]] std::string toString() const override;
    VarAssignNode(Token varToken, std::shared_ptr<ASTNode> &value): varToken(std::move(varToken)), value(value) {}
};


struct VarAccessNode: ASTNode {
    Token varToken;

    [[nodiscard]] std::string toString() const override;
    explicit VarAccessNode(Token varToken): varToken(std::move(varToken)) {}
};

#endif //KIRAAK_ASTNODES_H
