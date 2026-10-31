#pragma once

#include <string>
#include <cstdint>

namespace compiler::token{
  // Enum representing different types of tokens in the source code 256 too small for all possible token types
  enum class TokenTypes: std::uint16_t {
    Int,
    Return,
    Lparen,
    Rparen,
    Lbrack,
    Rbrack,
    Lbrace,
    Rbrace,
    Semicolon,
    Plus,
    Minus,
    Number,
    Equals,
    Identifier,
    EndOfFile
  };

  // Token structure representing a single token in the source code
  struct Token {
    TokenTypes type; // The type of the token (e.g., Int, Return, Plus, etc.)
    std::string token; // The actual token string from the source code
  };
} // namespace compiler::token