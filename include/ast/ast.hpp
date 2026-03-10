#pragma once
#include <memory>
#include <string>
#include <vector>

using namespace std;

namespace c2x64 {

    // ===== Expressions =====

    struct Expr {
        virtual ~Expr() = default;
    };

    struct NumberExpr : Expr {
        int value;

        explicit NumberExpr(int v) : value(v) {}
    };

    // ===== Statements =====

    struct Stmt {
        virtual ~Stmt() = default;
    };

    struct ReturnStmt : Stmt {
        unique_ptr<Expr> expr;

        explicit ReturnStmt(unique_ptr<Expr> e) : expr(std::move(e)) {}
    };

    // ===== Function =====

    struct FunctionDecl {
        string name;
        vector<unique_ptr<Stmt>> body;
    };

} 