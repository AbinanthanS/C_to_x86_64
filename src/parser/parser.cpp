#include "parser/parser.hpp"

#include <stdexcept>

namespace c2x64 {

Parser::Parser(std::vector<Token> tokens)
    : tokens_(std::move(tokens)) {}

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

std::unique_ptr<FunctionDecl> Parser::parse_function() {
    if (!match(TokenType::KwInt))
        throw std::runtime_error("expected 'int'");

    Token name = advance();

    if (name.type != TokenType::Identifier)
        throw std::runtime_error("expected function name");

    if (!match(TokenType::LParen))
        throw std::runtime_error("expected '('");

    if (!match(TokenType::RParen))
        throw std::runtime_error("expected ')'");

    if (!match(TokenType::LBrace))
        throw std::runtime_error("expected '{'");

    auto func = std::make_unique<FunctionDecl>();
    func->name = name.lexeme;

    while (!match(TokenType::RBrace)) {
        func->body.push_back(parse_statement());
    }

    return func;
}

// --------------------------

std::unique_ptr<Stmt> Parser::parse_statement() {
    if (peek().type == TokenType::KwReturn)
        return parse_return();

    throw std::runtime_error("unknown statement");
}

std::unique_ptr<Stmt> Parser::parse_return() {
    advance(); // return

    auto expr = parse_expression();

    if (!match(TokenType::Semicolon))
        throw std::runtime_error("expected ';'");

    return std::make_unique<ReturnStmt>(std::move(expr));
}

// --------------------------

std::unique_ptr<Expr> Parser::parse_expression() {
    Token t = advance();

    if (t.type == TokenType::Number)
        return std::make_unique<NumberExpr>(t.number_value);

    throw std::runtime_error("expected expression");
}

}