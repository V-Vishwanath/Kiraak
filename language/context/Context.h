
#ifndef KIRAAK_CONTEXT_H
#define KIRAAK_CONTEXT_H


#include "../token/ParsePosition.h"

#include <string>
#include <memory>


struct Context {
    std::string contextName;
    ParsePosition parentCallPos;
    std::shared_ptr<Context> parent;

    explicit Context(std::string_view contextName): contextName(contextName) {}
};


#endif //KIRAAK_CONTEXT_H
