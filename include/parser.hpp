#pragma once

#include "token.hpp"
#include <cstddef>
#include <vector>

namespace compiler::psr {
    // Parser class for processing the tokens produced by the Lexer
    class Parser {
        private:
            const std::vector<token::Token>& tokens; // Reference to the token vector, which must outlive the Parser
            std::size_t position = 0; // Index of the token currently being processed

        public:
            explicit Parser(const std::vector<token::Token>& tokens); // Constructor for the Parser class, takes the vector of tokens to be parsed

            void parse(); // Method to walk through the tokens; parsing rules are not implemented yet
    };
} // namespace compiler::psr
