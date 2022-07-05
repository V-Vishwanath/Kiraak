cmake_minimum_required(VERSION 3.22)
project(Kiraak)

set(CMAKE_CXX_STANDARD 17)

add_executable(Kiraak main.cpp language/token/Token.cpp language/token/Token.h language/syntax_types/SyntaxTypes.cpp language/syntax_types/SyntaxTypes.h language/ast_nodes/ASTNodes.cpp language/ast_nodes/ASTNodes.h language/errors/Errors.cpp language/errors/Errors.h language/token/ParsePosition.h language/lexer/Lexer.cpp language/lexer/Lexer.h language/parser/Parser.cpp language/parser/Parser.h language/interpreter/Interpreter.cpp language/interpreter/Interpreter.h language/datatypes/DataTypes.cpp language/datatypes/DataTypes.h language/utils/Utils.h language/utils/ResultWrappers.h language/context/Context.h language/context/SymbolTable.h language/ast_nodes/ASTNode.h language/datatypes/Datatype.h)
