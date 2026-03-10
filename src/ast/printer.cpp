#include "ast/printer.hpp"

#include <iostream>

namespace c2x64 {

static void indent(int level) {
    for (int i = 0; i < level; i++)
        std::cout << "  ";
}

static void print_expr(const Expr* expr, int level) {
    if (auto num = dynamic_cast<const NumberExpr*>(expr)) {
        indent(level);
        std::cout << "Number " << num->value << "\n";
    }
}

static void print_stmt(const Stmt* stmt, int level) {
    if (auto ret = dynamic_cast<const ReturnStmt*>(stmt)) {
        indent(level);
        std::cout << "Return\n";

        print_expr(ret->expr.get(), level + 1);
    }
}

void print_ast(const FunctionDecl& fn) {
    std::cout << "Function " << fn.name << "\n";

    for (const auto& stmt : fn.body) {
        print_stmt(stmt.get(), 1);
    }
}

}