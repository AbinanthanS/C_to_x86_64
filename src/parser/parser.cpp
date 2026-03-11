#include "parser/parser.hpp"

#include <stdexcept>

using namespace std;

namespace c2x64 {

    Parser::Parser(vector<Token> tokens) : tokens_(move(tokens)) {}

    Token& Parser::peek() {
        return tokens_[pos_];
    }

    Token& Parser::advance() {
        return tokens_[pos_++];
    }

    bool Parser::match(TokenType type) {
        if (peek().type == type) {
            advance();
            return true;
        }
        return false;
    }

    // --------------------------

    unique_ptr<FunctionDecl> Parser::parse_function() {
        if (!match(TokenType::KwInt))
            throw runtime_error("expected 'int'");

        Token name = advance();

        if (name.type != TokenType::Identifier)
            throw runtime_error("expected function name");

        if (!match(TokenType::LParen))
            throw runtime_error("expected '('");

        if (!match(TokenType::RParen))
            throw runtime_error("expected ')'");

        if (!match(TokenType::LBrace))
            throw runtime_error("expected '{'");

        auto func = make_unique<FunctionDecl>();
        func->name = name.lexeme;

        while (!match(TokenType::RBrace)) {
            func->body.push_back(parse_statement());
        }

        return func;
    }

    // --------------------------

    unique_ptr<Stmt> Parser::parse_statement() {
        if (peek().type == TokenType::KwReturn)
            return parse_return();

        throw runtime_error("unknown statement");
    }

    unique_ptr<Stmt> Parser::parse_return() {
        advance(); // return

        auto expr = parse_expression();

        if (!match(TokenType::Semicolon))
            throw runtime_error("expected ';'");

        return make_unique<ReturnStmt>(move(expr));
    }

    // --------------------------

    unique_ptr<Expr> Parser::parse_expression() {
        Token t = advance();

        if (t.type == TokenType::Number)
            return make_unique<NumberExpr>(t.number_value);

        throw runtime_error("expected expression");
    }

}