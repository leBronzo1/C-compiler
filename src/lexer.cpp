#include "../include/lexer.hpp"

#include <iostream>
#include <cctype>
#include <filesystem>
#include <stdexcept>

namespace compiler::lxr {
  Lexer::Lexer(const std::string &filename) {
    // Some file streams report EOF when reading a directory instead of a read error.
    if (std::filesystem::is_directory(filename)) {
      throw std::runtime_error("Can't read source file: path is a directory");
    }

    file.open(filename, std::ios::in);
    if(!file.is_open()) {
      std::cout << "Can't open file will include some kind of bool in class for fails" << std::endl;
      std::exit(-1);
    }

    keywords = {
        {"int", token::TokenTypes::Int},
        {"return", token::TokenTypes::Return},
        {"(", token::TokenTypes::Lparen},
        {")", token::TokenTypes::Rparen},
        {"[", token::TokenTypes::Lbrack},
        {"]", token::TokenTypes::Rbrack},
        {"+", token::TokenTypes::Plus},
        {"-", token::TokenTypes::Minus},
        {"=", token::TokenTypes::Equals},
        {"{", token::TokenTypes::Lbrace},
        {"}", token::TokenTypes::Rbrace},
        {";", token::TokenTypes::Semicolon}
    };
  }

  std::vector<token::Token> Lexer::tokenize() {
    std::vector<token::Token> tokens;
    char current;

    /*
    Loops through file one char at a time then checks if its a letter (If is number looks 
    through until space/non letter apperars then searches map for a match otherwise its 
    considered an identifier) similar for numbers minus and the identifier just read it
    a bit I dont want to write an essay should be self explanitory
    */

    while (file.get(current)) {
        if (std::isspace(static_cast<unsigned char>(current))) continue;

        if (std::isalpha(static_cast<unsigned char>(current)) || current == '_') {
            std::string word;
            word += current;

            while (file.peek() != EOF &&
                  (std::isalnum(static_cast<unsigned char>(file.peek())) || file.peek() == '_')) {
                word += static_cast<char>(file.get());
            }

            auto index = keywords.find(word);

            if (index != keywords.end()) {
                tokens.push_back({index->second, word});
            } else {
                tokens.push_back({token::TokenTypes::Identifier, word});
            }
        } else if (std::isdigit(static_cast<unsigned char>(current))) {
            std::string number;
            number += current;

            while (file.peek() != EOF &&
                  std::isdigit(static_cast<unsigned char>(file.peek()))) {
                number += static_cast<char>(file.get());
            }

            tokens.push_back({token::TokenTypes::Number, number});
        } else {
            std::string symbol(1, current);

            auto index = keywords.find(symbol);

            if (index != keywords.end()) {
                tokens.push_back({index->second, symbol});
            } else {
                std::cerr << "Unknown symbol: " << symbol << '\n';
                throw std::runtime_error("Unknown symbol: " + symbol);
            }
        }
    }

    if (file.bad() || !file.eof()) {
        throw std::runtime_error("Failed to read source file");
    }

    tokens.push_back({token::TokenTypes::EndOfFile, ""});

    return tokens;

  }
}
