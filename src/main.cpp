#include <iostream>
#include <string>
#include <vector>
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
)";
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

    // Phase 1 onward: compile pipeline goes here.
    cerr << "error: compiler pipeline not implemented yet\n";
    return 2;
}
