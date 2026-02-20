#include "doctest.h"
#include "lexer/lexer.hpp"
#include <vector>

using c2x64::Lexer;
using c2x64::TokenType;

static std::vector<TokenType> types_of(Lexer& lex) {
    std::vector<TokenType> out;
    while (true) {
        auto t = lex.next();
        out.push_back(t.type);
        if (t.type == TokenType::End) break;
    }
    return out;
}

TEST_CASE("lexer: keywords identifiers numbers") {
    Lexer lex("int main(){ return 42; }");
    auto got = types_of(lex);

    std::vector<TokenType> expect = {
        TokenType::KwInt,
        TokenType::Identifier, // main
        TokenType::LParen,
        TokenType::RParen,
        TokenType::LBrace,
        TokenType::KwReturn,
        TokenType::Number,
        TokenType::Semicolon,
        TokenType::RBrace,
        TokenType::End
    };

    CHECK(got == expect);
}

TEST_CASE("lexer: operators") {
    Lexer lex("a==b != c <= d >= e = f < g > h");
    auto got = types_of(lex);

    std::vector<TokenType> expect = {
        TokenType::Identifier,
        TokenType::EqEq,
        TokenType::Identifier,
        TokenType::NotEq,
        TokenType::Identifier,
        TokenType::LessEq,
        TokenType::Identifier,
        TokenType::GreaterEq,
        TokenType::Identifier,
        TokenType::Assign,
        TokenType::Identifier,
        TokenType::Less,
        TokenType::Identifier,
        TokenType::Greater,
        TokenType::Identifier,
        TokenType::End
    };

    CHECK(got == expect);
}

TEST_CASE("lexer: line comments") {
    Lexer lex("int x; // comment\nreturn 0;");
    auto got = types_of(lex);

    std::vector<TokenType> expect = {
        TokenType::KwInt,
        TokenType::Identifier,
        TokenType::Semicolon,
        TokenType::KwReturn,
        TokenType::Number,
        TokenType::Semicolon,
        TokenType::End
    };

    CHECK(got == expect);
}