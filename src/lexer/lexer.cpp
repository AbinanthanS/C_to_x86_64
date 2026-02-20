#include "lexer/lexer.hpp"
#include <cctype>
#include <string>

namespace c2x64 {

static bool is_ident_start(char c) {
    return std::isalpha(static_cast<unsigned char>(c)) || c == '_';
}
static bool is_ident_continue(char c) {
    return std::isalnum(static_cast<unsigned char>(c)) || c == '_';
}

Lexer::Lexer(std::string_view input) : input_(input) {}

char Lexer::current() const {
    return eof() ? '\0' : input_[i_];
}
char Lexer::lookahead() const {
    return (i_ + 1 >= input_.size()) ? '\0' : input_[i_ + 1];
}
bool Lexer::eof() const {
    return i_ >= input_.size();
}

void Lexer::advance() {
    if (eof()) return;

    char c = input_[i_++];
    if (c == '\n') {
        loc_.line++;
        loc_.col = 1;
    } else {
        loc_.col++;
    }
}

void Lexer::skip_whitespace_and_comments() {
    while (!eof()) {
        char c = current();

        // whitespace
        if (c == ' ' || c == '\t' || c == '\r' || c == '\n') {
            advance();
            continue;
        }

        // line comment: //
        if (c == '/' && lookahead() == '/') {
            while (!eof() && current() != '\n') advance();
            continue;
        }

        break;
    }
}

Token Lexer::make_simple(TokenType type, std::string lexeme, SourceLocation start) {
    Token t;
    t.type = type;
    t.lexeme = std::move(lexeme);
    t.loc = start;
    return t;
}

Token Lexer::lex_token() {
    skip_whitespace_and_comments();

    SourceLocation start = loc_;
    if (eof()) {
        Token t;
        t.type = TokenType::End;
        t.loc = start;
        t.lexeme = "";
        return t;
    }

    char c = current();

    // Identifiers / keywords
    if (is_ident_start(c)) {
        size_t begin = i_;
        while (!eof() && is_ident_continue(current())) advance();
        std::string word(input_.substr(begin, i_ - begin));

        Token t;
        t.loc = start;
        t.lexeme = word;

        if (word == "int") t.type = TokenType::KwInt;
        else if (word == "return") t.type = TokenType::KwReturn;
        else if (word == "if") t.type = TokenType::KwIf;
        else if (word == "else") t.type = TokenType::KwElse;
        else if (word == "while") t.type = TokenType::KwWhile;
        else if (word == "for") t.type = TokenType::KwFor;
        else t.type = TokenType::Identifier;

        return t;
    }

    // Numbers (decimal integers only)
    if (std::isdigit(static_cast<unsigned char>(c))) {
        size_t begin = i_;
        while (!eof() && std::isdigit(static_cast<unsigned char>(current()))) advance();
        std::string digits(input_.substr(begin, i_ - begin));

        Token t;
        t.type = TokenType::Number;
        t.loc = start;
        t.lexeme = digits;
        // simple parse; later you can add overflow checks
        t.number_value = std::stoll(digits);
        return t;
    }

    // Two-char operators
    if (c == '=' && lookahead() == '=') { advance(); advance(); return make_simple(TokenType::EqEq, "==", start); }
    if (c == '!' && lookahead() == '=') { advance(); advance(); return make_simple(TokenType::NotEq, "!=", start); }
    if (c == '<' && lookahead() == '=') { advance(); advance(); return make_simple(TokenType::LessEq, "<=", start); }
    if (c == '>' && lookahead() == '=') { advance(); advance(); return make_simple(TokenType::GreaterEq, ">=", start); }

    // Single-char tokens
    switch (c) {
        case '+': advance(); return make_simple(TokenType::Plus, "+", start);
        case '-': advance(); return make_simple(TokenType::Minus, "-", start);
        case '*': advance(); return make_simple(TokenType::Star, "*", start);
        case '/': advance(); return make_simple(TokenType::Slash, "/", start);
        case '%': advance(); return make_simple(TokenType::Percent, "%", start);

        case '=': advance(); return make_simple(TokenType::Assign, "=", start);
        case '<': advance(); return make_simple(TokenType::Less, "<", start);
        case '>': advance(); return make_simple(TokenType::Greater, ">", start);

        case '(': advance(); return make_simple(TokenType::LParen, "(", start);
        case ')': advance(); return make_simple(TokenType::RParen, ")", start);
        case '{': advance(); return make_simple(TokenType::LBrace, "{", start);
        case '}': advance(); return make_simple(TokenType::RBrace, "}", start);
        case ';': advance(); return make_simple(TokenType::Semicolon, ";", start);
        case ',': advance(); return make_simple(TokenType::Comma, ",", start);
        default:
            // unknown char
            advance();
            return make_simple(TokenType::Invalid, std::string(1, c), start);
    }
}

Token Lexer::next() {
    if (has_peek_) {
        has_peek_ = false;
        return peek_tok_;
    }
    return lex_token();
}

Token Lexer::peek() {
    if (!has_peek_) {
        peek_tok_ = lex_token();
        has_peek_ = true;
    }
    return peek_tok_;
}

} // namespace c2x64
