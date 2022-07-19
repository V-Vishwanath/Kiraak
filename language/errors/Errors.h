
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
    // Illegal char errors
    std::string UNEXPECTED_CHAR(char chr);

    const std::string_view DECIMAL_AFTER_DECIMAL =
        "Kya karre ji? Kya hai ye? Ek chukka lagne ke baad doosra lagta kya? Kyatobi likhre ji aap!";

    // Illegal syntax errors
    const std::string_view EXPECTED_NUMBER =
        "Ye idhar kuch galat aagaya!";

    const std::string_view EXPECTED_MATH_OPERATOR =
        "Ab 2 numberon ka kya karne ka? +, - *, /, ^, % kuch tho batao!";

    const std::string_view EXPECTED_RPAREN =
        "Ye jo '(' se khula hai usko ')' se bandh karne ka bhi hai miya!";

    const std::string_view EXPECTED_THO =
        "'tho' daalna ich bhool gaye ji aap! Agar kuch hua 'tho' kuch karne ka na!";

    const std::string_view EXPECTED_VAR_NAME =
        "Idhar koi naam aana tha. Uss naam ka variable banke rahega. Ye idhar kuch galat aagaya!";

    const std::string_view EXPECTED_BANAKE =
        "Aise comma daalke khaali variables ban sakte hai. Ye sab kya aa raha hai?!";

    const std::string_view EXPECTED_RAKH =
        "'Banake' ke baad 'rakh' aana hai! Tabhi tho uska kuch matlab banta hai na miya!";

    const std::string_view EXPECTED_HAI =
        "'hai' ke bina hindi hindi ich nahi hai miyaa! Jara 'hai' daala karo last mein!";


    // Runtime errors
    std::string VAR_NOT_DEFINED(std::string_view varname);

    std::string UNDEFINED_BIN_OP_NUM(std::size_t sIndex, std::size_t eIndex);
    std::string UNDEFINED_BIN_OP_BOOL(std::size_t sIndex, std::size_t eIndex);

    const std::string_view DIVISION_BY_ZERO =
        "Ye 0 se divide nahi karsakte re baap!";

    const std::string_view SIGNED_NON_NUMBER =
        "Ye + or - sirf numbers ke saamne lagte hai!";

    const std::string_view NON_BOOLEAN_INVERSION =
        "Ye idhar aane ka koi matlab ich nahi hai. 'sahi' ya 'galat' ke saath hi 'nahi' lagne ka!";

    const std::string_view INVALID_BIN_OP =
        "Aise do alag alag cheezon ke saath ye sab nahi kar sakte!";

    const std::string_view NON_BOOLEAN_COMP =
        "Condition sahi ya galat hone ka. Iska koi matlab ich nahi hai!";
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


struct IllegalCharError: public Error {
    std::string toString() override;
    IllegalCharError (std::string_view msg, const Token &token): Error(ErrorType::ILLEGAL_CHAR, msg, token) {}
};


struct InvalidSyntaxError: public Error {
    std::string toString() override;
    InvalidSyntaxError(std::string_view msg, const Token &token): Error(ErrorType::INVALID_SYNTAX, msg, token) {}
};


#endif //KIRAAK_ERRORS_H
