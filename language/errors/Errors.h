
#ifndef KIRAAK_ERRORS_H
#define KIRAAK_ERRORS_H

#include "../token/Token.h"
#include "../context/Context.h"
#include "../token/ParsePosition.h"

#include <regex>
#include <string>
#include <utility>
#include <sstream>
#include <iostream>


namespace ErrorType {
    const std::string_view RUNTIME = "RuntimeError";
    const std::string_view ILLEGAL_CHAR = "IllegalCharError";
    const std::string_view INVALID_SYNTAX = "InvalidSyntaxError";
}

namespace ErrorMsg {
    std::string UNEXPECTED_CHAR(char chr);

    const std::string_view DECIMAL_AFTER_DECIMAL =
        "Kya karre ji? Kya hai ye? Ek chukka lagne ke baad doosra lagta kya? Kyatobi likhre ji aap!";

    const std::string_view EXPECTED_NUMBER =
        "Maaki kirikiri idhar tho number ya koi variable aane ka na miya!!";

    const std::string_view EXPECTED_MATH_OPERATOR =
        "Ab 2 numberon ka kya karne ka? +, - *, /, ^, % kuch tho batao!";

    const std::string_view EXPECTED_RPAREN =
        "Ye jo '(' se khula hai usko ')' se bandh karne ka bhi hai miya!";


    const std::string_view DIVISION_BY_ZERO =
        "Ye 0 se divide nahi karsakte re baap!";

    std::string VAR_NOT_DEFINED(std::string_view varname);
}


class Error {
    std::string msg;
    std::string_view name;

protected:
    const Token token;

    [[nodiscard]] std::string compileTimeError() const;
    [[nodiscard]] std::string getUnderlinedError() const;

    Error(std::string_view name, std::string_view msg, Token token): name(name), msg(msg), token(std::move(token)) {}

public:
    static std::string SOURCE_CODE;

    virtual ~Error() = default;
    virtual std::string toString() = 0;
};



class RuntimeError: public Error {
    const Context ctx;

public:
    RuntimeError(std::string_view msg, const Token &token, Context ctx):
        Error(ErrorType::RUNTIME, msg, token), ctx(std::move(ctx)) {}

    std::string toString() override;
    [[nodiscard]] std::string stackTrace() const;
};


struct IllegalCharError: Error {
    std::string toString() override;
    IllegalCharError (std::string_view msg, const Token &token): Error(ErrorType::ILLEGAL_CHAR, msg, token) {}
};


struct InvalidSyntaxError: Error {
    std::string toString() override;
    InvalidSyntaxError(std::string_view msg, const Token &token): Error(ErrorType::INVALID_SYNTAX, msg, token) {}
};


#endif //KIRAAK_ERRORS_H
