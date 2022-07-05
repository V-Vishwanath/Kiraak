
#ifndef KIRAAK_CONTEXT_H
#define KIRAAK_CONTEXT_H


#include "../token/ParsePosition.h"
#include "SymbolTable.h"

#include <string>
#include <memory>


struct Context {
    std::string contextName;
    SymbolTable symbolTable;
    ParsePosition parentCallPos;
    std::shared_ptr<Context> parent;

    explicit Context(std::string_view contextName): contextName(contextName) {}
};


#endif //KIRAAK_CONTEXT_H
