#pragma once

#include "token.hpp"
#include "abstract_syntax_tree.hpp"

#include <cstddef>
#include <memory>
#include <vector>

namespace compiler::psr {
  // Parser class for turning lexer tokens into an abstract syntax tree
  class Parser {
    private:
      const std::vector<token::Token>& tokens; // Reference to the lexer tokens, which must outlive the Parser
      std::size_t position = 0; // Index of the token currently being processed

      const token::Token& current() const; // Returns the current token; throws if there are no tokens left
      const token::Token& consume(token::TokenTypes expected); // Checks the token type and moves forward; throws if it does not match

      std::unique_ptr<ast::Function> parseFunction(); // Parses an int function with no parameters (e.g., int main() { ... })
      std::vector<std::unique_ptr<ast::Statement>> parseBlock(); // Parses the declarations and return statements between braces

      std::unique_ptr<ast::Statement> parseDeclaration(); // Parses an initialized int variable (e.g., int x = 5;)
      std::unique_ptr<ast::Statement> parseReturn(); // Parses a return statement and its value (e.g., return x;)

      std::unique_ptr<ast::Expression> parseExpression(); // Parses addition and subtraction from left to right
      std::unique_ptr<ast::Expression> parsePrimary(); // Parses a number, identifier, or expression inside parentheses

    public:
      explicit Parser(const std::vector<token::Token>& tokens); // Constructor for the Parser class, takes the tokens produced by the Lexer
      std::unique_ptr<ast::Program> parse(); // Parses functions until EndOfFile and returns the tree; throws on invalid syntax
  };
} // namespace compiler::psr
