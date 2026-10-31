#include "../include/parser.hpp"

namespace compiler::psr {

    Parser::Parser(const std::vector<token::Token>& tokens) : tokens(tokens) {}

    void Parser::parse() {
        while (position < tokens.size()) {
            const token::Token& current = tokens[position];

            
            ++position;
        }
}

}