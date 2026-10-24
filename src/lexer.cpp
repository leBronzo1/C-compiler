#include "lexer.hpp"
#include <fstream>
#include <print>

namespace lxr {
  Lexer::Lexer(const std::string &filename) {
    file.open(filename, std::ios::in | std::ios::out | std::ios::app); // means inpout, output, write to end of file(EOF)
    if(file.is_open()) std::println("Can't open file will include some kind of bool in class for fails"); 
  }  
}
