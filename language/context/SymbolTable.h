
#ifndef KIRAAK_SYMBOLTABLE_H
#define KIRAAK_SYMBOLTABLE_H


#include "../datatypes/Datatype.h"

#include <memory>
#include <unordered_map>


class SymbolTable {
    std::shared_ptr<SymbolTable> parentSymbols;
    std::unordered_map<std::string, std::shared_ptr<DataType>> symbols;

public:
    std::shared_ptr<DataType> get(const std::string &varname) const { // NOLINT(misc-no-recursion)
        if (auto it = symbols.find(varname); it != symbols.end()) return it->second;
        if (parentSymbols != nullptr) return parentSymbols->get(varname);
        return nullptr;
    }

    void remove(const std::string &varname) { symbols.erase(varname); }
    void set (const std::string &varname, std::shared_ptr<DataType> &value) { symbols[varname] = value; }
};


#endif //KIRAAK_SYMBOLTABLE_H
