
#ifndef KIRAAK_RESULTWRAPPERS_H
#define KIRAAK_RESULTWRAPPERS_H


#include "../token/Token.h"
#include "../errors/Errors.h"
#include "../ast_nodes/_ASTNode.h"
#include "../datatypes/_Datatype.h"

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
