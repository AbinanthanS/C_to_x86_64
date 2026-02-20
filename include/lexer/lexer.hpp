#pragma once
#include <string_view>
#include <string>
#include "lexer/token.hpp"

namespace c2x64 {

class Lexer {
public:
    explicit Lexer(std::string_view input);

    Token next();
    Token peek();

private:
    Token lex_token();

    char current() const;
    char lookahead() const;
    bool eof() const;

    void advance();
    void skip_whitespace_and_comments();

    Token make_simple(TokenType type, std::string lexeme, SourceLocation start);

    std::string_view input_;
    size_t i_ = 0;
    SourceLocation loc_{1,1};

    bool has_peek_ = false;
    Token peek_tok_;
};

} // namespace c2x64