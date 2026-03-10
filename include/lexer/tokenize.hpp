#pragma once

#include <vector>
#include <string>

#include "lexer/lexer.hpp"

namespace c2x64 {

inline std::vector<Token> tokenize(const std::string& src) {
    Lexer lex(src);

    std::vector<Token> tokens;

    while (true) {
        Token t = lex.next();
        tokens.push_back(t);

        if (t.type == TokenType::End)
            break;
    }

    return tokens;
}

}