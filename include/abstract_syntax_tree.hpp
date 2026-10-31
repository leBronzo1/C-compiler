
#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace compiler::ast {
  /*
  Each node stores one part of the source code. Nodes own their children through
  unique_ptr so deleting the Program also cleans up the rest of the tree. The
  constructors use std::move to transfer strings and child nodes into their fields.
  */

  // Base structure for all nodes in the abstract syntax tree
  struct Node {
    virtual ~Node() = default; // Allows derived nodes to be cleaned up through a base pointer
  };

  struct Expression : Node {}; // Base type for expressions that produce a value
  struct Statement : Node {}; // Base type for statements inside a function body

  // Number structure representing an integer literal (e.g., 123)
  struct Number : Expression {
    int value; // The integer value read from the number token

    explicit Number(int value) : value(value) {}
  };

  // Identifier structure representing a variable used in an expression
  struct Identifier : Expression {
    std::string name; // The name of the variable (e.g., my_var)

    explicit Identifier(std::string name) : name(std::move(name)) {}
  };

  // BinaryExpression structure representing addition or subtraction (e.g., x + 5)
  struct BinaryExpression : Expression {
    std::string op; // The operator string, currently only "+" or "-"
    std::unique_ptr<Expression> left; // The expression on the left side of the operator
    std::unique_ptr<Expression> right; // The expression on the right side of the operator

    BinaryExpression(std::string op, std::unique_ptr<Expression> left, std::unique_ptr<Expression> right)
        : op(std::move(op)), left(std::move(left)), right(std::move(right)) {}
  };

  // VariableDeclaration structure representing an initialized int variable (e.g., int x = 5;)
  struct VariableDeclaration : Statement {
    std::string name; // The name of the variable being declared
    std::unique_ptr<Expression> value; // The expression used to initialize the variable

    VariableDeclaration(std::string name, std::unique_ptr<Expression> value)
        : name(std::move(name)), value(std::move(value)) {}
  };

  // ReturnStatement structure representing a return and its value (e.g., return x;)
  struct ReturnStatement : Statement {
    std::unique_ptr<Expression> value; // The expression whose value is returned from the function

    explicit ReturnStatement(std::unique_ptr<Expression> value) : value(std::move(value)) {}
  };

  // Function structure representing an int function with no parameters
  struct Function : Node {
    std::string name; // The name of the function (e.g., main)
    std::vector<std::unique_ptr<Statement>> body; // The statements inside the braces, in source order
  };

  // Program structure representing the entire parsed source file
  struct Program : Node {
    std::vector<std::unique_ptr<Function>> functions; // The functions in the source file, in source order
  };
} // namespace compiler::ast
