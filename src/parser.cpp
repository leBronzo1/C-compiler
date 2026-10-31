#include "../include/parser.hpp"

#include <stdexcept>
#include <string>
#include <utility>

namespace compiler::psr {
  Parser::Parser(const std::vector<token::Token> &tokens) : tokens(tokens) {}

  // Get the current token without moving forward
  const token::Token &Parser::current() const {
    if (position >= tokens.size()) {
      throw std::runtime_error("Unexpected end of tokens");
    }

    return tokens[position];
  }

  // Check that the current token is the expected type, then move to the next one
  const token::Token &Parser::consume(token::TokenTypes expected) {
    if (current().type != expected) {
      throw std::runtime_error("Unexpected token: " + current().token);
    }

    return tokens[position++];
  }

  std::unique_ptr<ast::Program> Parser::parse() {
    auto program = std::make_unique<ast::Program>();

    /*
    Loops through the tokens one function at a time until EndOfFile. Each function
    parses its own body, and the statements in that body parse their expressions.
    The resulting nodes are added to the Program in the same order as the source.
    */

    while (current().type != token::TokenTypes::EndOfFile) {
      program->functions.push_back(parseFunction());
    }

    return program;
  }

  // Parse an int function with no parameters (e.g., int main() { ... })
  std::unique_ptr<ast::Function> Parser::parseFunction() {
    consume(token::TokenTypes::Int);

    std::string name = consume(token::TokenTypes::Identifier).token;

    consume(token::TokenTypes::Lparen);
    consume(token::TokenTypes::Rparen);

    auto function = std::make_unique<ast::Function>();
    function->name = std::move(name);
    function->body = parseBlock();

    return function;
  }

  // Parse the statements between braces, currently only int declarations and returns
  std::vector<std::unique_ptr<ast::Statement>> Parser::parseBlock() {
    std::vector<std::unique_ptr<ast::Statement>> statements;

    consume(token::TokenTypes::Lbrace);

    while (current().type != token::TokenTypes::Rbrace) {
      if (current().type == token::TokenTypes::Int) {
        statements.push_back(parseDeclaration());
      } else if (current().type == token::TokenTypes::Return) {
        statements.push_back(parseReturn());
      } else {
        throw std::runtime_error("Unexpected statement: " + current().token);
      }
    }

    consume(token::TokenTypes::Rbrace);
    return statements;
  }

  // Parse an initialized int variable (e.g., int x = 5 + 2;)
  std::unique_ptr<ast::Statement> Parser::parseDeclaration() {
    consume(token::TokenTypes::Int);

    std::string name = consume(token::TokenTypes::Identifier).token;

    consume(token::TokenTypes::Equals);

    auto value = parseExpression();

    consume(token::TokenTypes::Semicolon);

    return std::make_unique<ast::VariableDeclaration>(std::move(name), std::move(value));
  }

  // Parse a return statement and its expression (e.g., return x + 1;)
  std::unique_ptr<ast::Statement> Parser::parseReturn() {
    consume(token::TokenTypes::Return);

    auto value = parseExpression();

    consume(token::TokenTypes::Semicolon);

    return std::make_unique<ast::ReturnStatement>(std::move(value));
  }

  // Parse addition and subtraction using the operators supported by the Lexer
  std::unique_ptr<ast::Expression> Parser::parseExpression() {
    auto left = parsePrimary();

    /*
    Each operator combines the tree built so far with the next expression. This
    makes + and - work from left to right, so 10 - 3 - 2 is read as (10 - 3) - 2.
    Parentheses are handled by parsePrimary before the expressions are combined.
    */

    while (current().type == token::TokenTypes::Plus ||
           current().type == token::TokenTypes::Minus) {
      std::string op = current().token;
      ++position;

      auto right = parsePrimary();

      left = std::make_unique<ast::BinaryExpression>(std::move(op), std::move(left), std::move(right));
    }

    return left;
  }

  // Parse a number, variable name, or expression inside parentheses
  std::unique_ptr<ast::Expression> Parser::parsePrimary() {
    if (current().type == token::TokenTypes::Number) {
      int value = std::stoi(current().token);
      ++position;

      return std::make_unique<ast::Number>(value);
    }

    if (current().type == token::TokenTypes::Identifier) {
      std::string name = current().token;
      ++position;

      return std::make_unique<ast::Identifier>(std::move(name));
    }

    if (current().type == token::TokenTypes::Lparen) {
      ++position;

      auto expression = parseExpression();

      consume(token::TokenTypes::Rparen);
      return expression;
    }

    throw std::runtime_error("Invalid expression: " + current().token);
  }
} // namespace compiler::psr
