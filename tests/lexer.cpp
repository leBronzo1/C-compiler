#include "../include/lexer.hpp"

#include <exception>
#include <iostream>

// Tokenize a source file and print each token's type and text
int lexer_test(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }

    try {
        std::string filename = argv[1];
        compiler::lxr::Lexer lexer(filename);

        std::vector<compiler::token::Token> tokens = lexer.tokenize();

        for (const auto& token : tokens) {
            std::cout << static_cast<int>(token.type) << " : " << token.token << '\n';
        }
    } catch (const std::exception& error) {
        std::cerr << "Lexer test failed: " << error.what() << '\n';
        return 1;
    }

    return 0;
}

// The compiler can still include lexer_test without defining another main function
#ifdef TEST_MAIN
int main(int argc, char* argv[]) {
    return lexer_test(argc, argv);
}
#endif
