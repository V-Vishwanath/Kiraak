#include <iostream>

#include "language/lexer/Lexer.h"
#include "language/parser/Parser.h"
#include "language/interpreter/Interpreter.h"



void run(std::string_view srcCode) {
    Error::SOURCE_CODE = srcCode;

    LexerResult lexRes = Lexer(srcCode).getTokens();
    if (lexRes.error.has_value()) {
        std::cout << lexRes.error.value().toString();
        return;
    }

    ResultAST parseRes = Parser(lexRes.tokens).genAST();
    if (parseRes.error.has_value()) {
        std::cout << parseRes.error.value().toString();
        return;
    }

    Context context("<program>");
    ASTParseResult res = Interpreter().parseAST(parseRes.rootNode.get(), context);
    if (res.error.has_value()) {
        std::cout << res.error.value().toString();
        return;
    }

    std::cout << res.data.get();
}


int main() {
    while (true) {
        std::cout << ">>> ";

        std::string srcCode;
        std::getline(std::cin, srcCode);

        if (srcCode == "exit()") break;

        run(srcCode);

        std::cout << "\n";
    }

    return 0;
}
