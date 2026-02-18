#pragma once
#include<cstdint>
#include<string>
#include<string_view>
using namespace std;

namespace c2x64{
    //useful for error reporting and debugging
    struct SourceLocation{
        int line = 1;
        int col = 1;
    };

    enum class TokenType{
        //special
        End, Invalid,
        //Identifiers and literals
        Identifier, Number,
        //Keywords
        KwInt, KwReturn, KwIf, KwElse, KwWhile, KwFor,
        //operators
        Plus, Minus, Star, Slash, Percent,
        Assign, EqEq, NotEq, Less, LessEq, Greater, GreaterEq,
        //Punctuation
        LParen, RParen, LBrace, RBrace, Semicolon, Comma
    };

    inline const char* token_type_name(TokenType t){
        switch (t) {
            case TokenType::End: return "End";
            case TokenType::Invalid: return "Invalid";
            case TokenType::Identifier: return "Identifier";
            case TokenType::Number: return "Number";
            case TokenType::KwInt: return "KwInt";
            case TokenType::KwReturn: return "KwReturn";
            case TokenType::KwIf: return "KwIf";
            case TokenType::KwElse: return "KwElse";
            case TokenType::KwWhile: return "KwWhile";
            case TokenType::KwFor: return "KwFor";
            case TokenType::Plus: return "Plus";
            case TokenType::Minus: return "Minus";
            case TokenType::Star: return "Star";
            case TokenType::Slash: return "Slash";
            case TokenType::Percent: return "Percent";
            case TokenType::Assign: return "Assign";
            case TokenType::EqEq: return "EqEq";
            case TokenType::NotEq: return "NotEq";
            case TokenType::Less: return "Less";
            case TokenType::LessEq: return "LessEq";
            case TokenType::Greater: return "Greater";
            case TokenType::GreaterEq: return "GreaterEq";
            case TokenType::LParen: return "LParen";
            case TokenType::RParen: return "RParen";
            case TokenType::LBrace: return "LBrace";
            case TokenType::RBrace: return "RBrace";
            case TokenType::Semicolon: return "Semicolon";
            case TokenType::Comma: return "Comma";
        }
        return "Unknown";
    }
    //A token produced by the lexer
    struct Token {
        TokenType type = TokenType::Invalid;
        string lexeme;
        SourceLocation loc{};
        int64_t number_value = 0; // valid if type == Number
    };
}