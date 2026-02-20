#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "lexer/lexer.hpp"
#include "lexer/token.hpp"

using namespace std;

static constexpr const char* kVersion = "0.0.1";

static void print_help() {
    cout <<
R"(c2x64 - C subset compiler targeting x86_64 (System V ABI)

Usage:
  c2x64 [options] <input.c>

Options:
  --help        Show this help
  --version     Show version
  --lex         Tokenize input and print tokens
)";
}

static bool read_file_to_string(const std::string& path, std::string& out) {
    std::ifstream in(path, std::ios::in | std::ios::binary);
    if (!in) return false;

    std::ostringstream ss;
    ss << in.rdbuf();
    out = ss.str();
    return true;
}

static int run_lex(const std::string& path) {
    std::string input;
    if (!read_file_to_string(path, input)) {
        std::cerr << "error: could not open file: " << path << "\n";
        return 1;
    }

    c2x64::Lexer lex(input);

    while (true) {
        c2x64::Token t = lex.next();

        std::cout << t.loc.line << ":" << t.loc.col << "  "
                  << c2x64::token_type_name(t.type)
                  << "  '" << t.lexeme << "'";

        if (t.type == c2x64::TokenType::Number) {
            std::cout << "  value=" << t.number_value;
        }

        std::cout << "\n";

        if (t.type == c2x64::TokenType::End) break;
    }

    return 0;
}

int main(int argc, char** argv) {
    vector<string> args(argv + 1, argv + argc);

    if (args.empty()) {
        print_help();
        return 1;
    }

    if (args.size() == 1 && (args[0] == "--help" || args[0] == "-h")) {
        print_help();
        return 0;
    }

    if (args.size() == 1 && (args[0] == "--version" || args[0] == "-v")) {
        cout << kVersion << "\n";
        return 0;
    }

    // --lex <file>
    if (args.size() == 2 && args[0] == "--lex") {
        return run_lex(args[1]);
    }

    // default: expect an input file (future phases)
    if (args.size() == 1) {
        std::cerr << "error: compile pipeline not implemented yet (try --lex)\n";
        return 2;
    }

    std::cerr << "error: unknown arguments (try --help)\n";
    return 1;
}