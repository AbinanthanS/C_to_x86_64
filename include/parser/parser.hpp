#pragma once

#include <vector>

#include "lexer/lexer.hpp"
#include "ast/ast.hpp"

using namespace std;

namespace c2x64 {

class Parser {
public:
    explicit Parser(vector<Token> tokens);

    unique_ptr<FunctionDecl> parse_function();

private:
    vector<Token> tokens_;
    size_t pos_ = 0;

    Token& peek();
    Token& advance();
    bool match(TokenType type);

    unique_ptr<Stmt> parse_statement();
    unique_ptr<Stmt> parse_return();

    unique_ptr<Expr> parse_expression();
};

}