#include <cstdint>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

enum class TokenTypes: std::uint8_t  {
  Int,
  Return,
  Lparen,
  Rparen,
  Lbrack,
  Rbrack,
  Plus,
  Minus,
  Number,
  Identifier,
  EndOfFile
};

struct Token {
  TokenTypes type;
  std::string token;
};

class Lexer {
  private:
    std::stringstream source;
    std::fstream file;
    std::vector<Token> tokens;
  public:
    explicit Lexer(const std::string& filename);
    std::vector<Token> tokenize();
};
