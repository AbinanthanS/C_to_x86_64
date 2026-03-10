#include "doctest.h"

#include "lexer/lexer.hpp"
#include "parser/parser.hpp"

using namespace c2x64;

TEST_CASE("parse simple function") {

    std::string src =
        "int main() { return 42; }";

    Lexer lex(src);

    std::vector<Token> tokens;

    while (true) {
        Token t = lex.next();
        tokens.push_back(t);
        if (t.type == TokenType::End)
            break;
    }

    Parser parser(tokens);

    auto func = parser.parse_function();

    CHECK(func->name == "main");
    CHECK(func->body.size() == 1);
}