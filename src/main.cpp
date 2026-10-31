#include "../include/lexer.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: ./compiler <filename>\n";
        return 1;
    }

    std::string filename = argv[1];
    compiler::lxr::Lexer lexer(filename);

    std::vector<compiler::token::Token> tokens = lexer.tokenize();

    for (const auto& token : tokens) {
        std::cout << static_cast<int>(token.type)
                  << " : " << token.token << '\n';
    }

    return 0;
}