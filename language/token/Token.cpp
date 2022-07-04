
#include "Token.h"


std::ostream &operator << (std::ostream &os, const Token &token) {
    os << "<" << token.type;

    if (token.value.has_value()) {
        os << "(";
        std::visit([&os] (const auto& val) { os << val; }, token.value.value());
        os << ")";
    }

    return os << ">";
}
