#include "../include/lexer.hpp"
#include <fstream>
#include <iostream>
#include <cstdlib>

namespace compiler::lxr {
  Lexer::Lexer(const std::string &filename) {
    file.open(filename, std::ios::in | std::ios::out | std::ios::app); // means inpout, output, write to end of file(EOF)
    if(!file.is_open()) {
      std::cout << "Can't open file will include some kind of bool in class for fails" << std::endl;
      std::exit(-1);
    }
  }

  std::vector<token::Token> Lexer::tokenize() {
    while(file.get()) {
      // Logic to be added after parser is done:
    }
    return tokens;
  }
}
