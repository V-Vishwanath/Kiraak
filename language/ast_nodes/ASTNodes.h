
#ifndef KIRAAK_ASTNODES_H
#define KIRAAK_ASTNODES_H


#include "../token/Token.h"
#include "../errors/Errors.h"

#include <sstream>
#include <utility>
#include <memory>


struct ASTNode {
    virtual ~ASTNode() = default;

    [[nodiscard]] virtual std::string toString() const = 0;
    friend std::ostream& operator << (std::ostream&, ASTNode*);
};


struct LiteralNode: ASTNode {
    Token token;

    [[nodiscard]] std::string toString() const override;
    explicit LiteralNode(const Token &token): token(token) {}
};


struct UnaryExprNode: ASTNode {
    Token opToken;
    std::shared_ptr<ASTNode> exprNode;

    [[nodiscard]] std::string toString() const override;
    UnaryExprNode(const Token &opToken, std::shared_ptr<ASTNode> &node): opToken(opToken), exprNode(node) {}
};


struct BinaryExprNode: ASTNode {
    Token opToken;
    std::shared_ptr<ASTNode> left, right;

    [[nodiscard]] std::string toString() const override;
    BinaryExprNode(std::shared_ptr<ASTNode> &left, const Token &opToken, std::shared_ptr<ASTNode> &right):
        left(left), opToken(opToken), right(right) {}
};

#endif //KIRAAK_ASTNODES_H
