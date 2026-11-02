#include "../include/codegen.hpp"

namespace compiler::cgen {
    explicit codeGeneration::codeGeneration(std::ostream& output) : output(output) {}

    void codeGeneration::generateFunction(const ast::Function& function) {
        output << ".text\n";
        output << ".globl _" << function.name << "\n";
        output << ".p2align 2\n";
        output << "_" << function.name << ":\n";

        for (const auto& statement : function.body) {
            generateStatement(*statement);
        }
    }

    void codeGeneration::generateStatement(const ast::Statement& statement) {
        if (auto* ret = dynamic_cast<const ast::ReturnStatement*>(&statement)) {
            generateExpression(*ret->value);
            output << "    ret\n";
        }
        else if (auto* var = dynamic_cast<const ast::VariableDeclaration*>(&statement)) {
            generateExpression(*var->value);
            // TODO: Store the result in the variable's stack location
        }
    }

    void codeGeneration::generateExpression(const ast::Expression& expression) {
        if (auto* num = dynamic_cast<const ast::Number*>(&expression)) {
            output << "    mov w0, #" << num->value << "\n";
        }
        else if (auto* id = dynamic_cast<const ast::Identifier*>(&expression)) {
            // TODO: Load the variable's value from the stack
        }
        else if (auto* binary = dynamic_cast<const ast::BinaryExpression*>(&expression)) {
            // TODO: Evaluate both operands and perform addition/subtraction
        }
    }
};