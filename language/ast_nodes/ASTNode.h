
#ifndef KIRAAK_ASTNODE_H
#define KIRAAK_ASTNODE_H

#include <string>


struct ASTNode {
    virtual ~ASTNode() = default;

    [[nodiscard]] virtual std::string toString() const = 0;
    friend std::ostream& operator << (std::ostream&, ASTNode*);
};

#endif //KIRAAK_ASTNODE_H
