
#ifndef KIRAAK_RESULTWRAPPERS_H
#define KIRAAK_RESULTWRAPPERS_H


#include "../token/Token.h"
#include "../ast_nodes/ASTNodes.h"
#include "../datatypes/DataTypes.h"

#include <vector>


struct LexerResult {
    std::vector<Token> tokens;
    std::optional<IllegalCharError> error;
};


struct ResultAST {
    std::shared_ptr<ASTNode> rootNode;
    std::optional<InvalidSyntaxError> error;
};


struct ASTParseResult {
    std::shared_ptr<DataType> data;
    std::optional<RuntimeError> error;
};


#endif //KIRAAK_RESULTWRAPPERS_H
