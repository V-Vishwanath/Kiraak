
#ifndef KIRAAK__ASTNODE_H
#define KIRAAK__ASTNODE_H


struct ASTNode {
    enum class TYPE {
        LITERAL,
        UNARY_EXPR,
        BINARY_EXPR,

        VAR_ACCESS,
        VAR_ASSIGNMENT,

        CONDITIONAL
    };

    virtual TYPE Type() = 0;
};

#endif //KIRAAK__ASTNODE_H
