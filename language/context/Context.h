
#ifndef KIRAAK_CONTEXT_H
#define KIRAAK_CONTEXT_H


#include "SymbolTable.h"
#include "../token/ParsePosition.h"


struct Context {
    std::string contextName;
    SymbolTable symbolTable;
    ParsePosition parentCallPos;
    std::shared_ptr<Context> parent;

    Context(): contextName("<program>") {}
    explicit Context(std::string_view contextName): contextName(contextName) {}
};


#endif //KIRAAK_CONTEXT_H
