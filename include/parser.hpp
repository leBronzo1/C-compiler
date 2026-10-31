#pragma once

#include "token.hpp"
#include <cstddef>
#include <vector>

namespace compiler::psr {
    class Parser {
        private:
            const std::vector<token::Token>& tokens;
            std::size_t position = 0;

        public:
            explicit Parser(const std::vector<token::Token>& tokens);

            void parse();
    };
}