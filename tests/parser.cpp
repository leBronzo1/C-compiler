#include "../include/lexer.hpp"
#include "../include/parser.hpp"

#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>

namespace {
  // Print an expression and indent its children to show how the parser grouped it
  void print_expression(const compiler::ast::Expression &expression, int indentation) {
    std::string padding(indentation, ' ');

    if (const auto* number = dynamic_cast<const compiler::ast::Number*>(&expression)) {
      std::cout << padding << "Number: " << number->value << '\n';
    } else if (const auto* identifier = dynamic_cast<const compiler::ast::Identifier*>(&expression)) {
      std::cout << padding << "Identifier: " << identifier->name << '\n';
    } else if (const auto* binary = dynamic_cast<const compiler::ast::BinaryExpression*>(&expression)) {
      std::cout << padding << "Binary expression: " << binary->op << '\n';
      print_expression(*binary->left, indentation + 2);
      print_expression(*binary->right, indentation + 2);
    } else {
      throw std::runtime_error("Unknown expression node");
    }
  }
} // namespace

// Tokenize a source file, parse it, and print the resulting abstract syntax tree
int parser_test(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }

    try {
        std::string filename = argv[1];
        compiler::lxr::Lexer lexer(filename);

        std::vector<compiler::token::Token> tokens = lexer.tokenize();
        compiler::psr::Parser parser(tokens);
        std::unique_ptr<compiler::ast::Program> program = parser.parse();

        std::cout << "Program\n";
        for (const auto& function : program->functions) {
            std::cout << "  Function: " << function->name << '\n';

            for (const auto& statement : function->body) {
                if (const auto* declaration = dynamic_cast<const compiler::ast::VariableDeclaration*>(statement.get())) {
                    std::cout << "    Variable declaration: " << declaration->name << '\n';
                    print_expression(*declaration->value, 6);
                } else if (const auto* returned = dynamic_cast<const compiler::ast::ReturnStatement*>(statement.get())) {
                    std::cout << "    Return\n";
                    print_expression(*returned->value, 6);
                } else {
                    throw std::runtime_error("Unknown statement node");
                }
            }
        }
    } catch (const std::exception& error) {
        std::cerr << "Parser test failed: " << error.what() << '\n';
        return 1;
    }

    return 0;
}

#ifdef TEST_MAIN
int main(int argc, char* argv[]) {
    return parser_test(argc, argv);
}
#endif
