#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>
#include "token.hpp"

namespace compiler::lxr {
  // Lexer class for tokenizing source code
  class Lexer {
    private:
      std::fstream file; // File stream for reading the source code from a file
      std::unordered_map<std::string, token::TokenTypes> keywords; // Maps supported keywords and symbols to their token types
    public:
      explicit Lexer(const std::string& filename); // Constructor for the Lexer class, takes the filename of the source code to be tokenized
      std::vector<token::Token> tokenize(); // Method to tokenize the source code and return the vector of tokens; throws on unknown symbols or stream read errors
};
} // namespace compiler::lxr
