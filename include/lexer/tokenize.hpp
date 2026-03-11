#pragma once

#include <vector>
#include <string>

#include "lexer/lexer.hpp"

using namespace std;

namespace c2x64 {

    inline vector<Token> tokenize(const string& src) {
        Lexer lex(src);

        vector<Token> tokens;

        while (true) {
            Token t = lex.next();
            tokens.push_back(t);

            if (t.type == TokenType::End)
                break;
        }

        return tokens;
    }

}