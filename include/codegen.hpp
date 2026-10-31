#pragma once

#include "abstract_syntax_tree.hpp"
#include <ostream>

namespace compiler::cgen {

    // Converts the AST into assembly code.
    class codeGeneration {
        private:
            std::ostream& output; // Stream for writing assembly instructions.

            void generateFunction(const ast::Function& function); // Generates assembly for a function.
            void generateStatement(const ast::Statement& statement); // Generates assembly for statements.
            void generateExpression(const ast::Expression& expression); // Generates assembly for expressions.
        public:
            explicit codeGeneration(std::ostream& output); // Initializes the assembly output stream.
            void generate(const ast::Program& program); // Generates assembly for the entire program.
    };

}