CXX = clang++
CXXFLAGS = -std=c++20 -Wall -Wextra -g -Iinclude

TARGET = compiler

SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)
DEP = $(OBJ:.o=.d)

TEST_FILE ?= tests/sample.c
TEST_TARGETS = tests/lexer_test tests/parser_test
TEST_OBJ = tests/lexer.o tests/parser.o
TEST_DEP = $(TEST_OBJ:.o=.d)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

# Give each test its own main function when building it as a standalone program
$(TEST_OBJ): tests/%.o: tests/%.cpp Makefile
	$(CXX) $(CXXFLAGS) -DTEST_MAIN -MMD -MP -c $< -o $@

tests/lexer_test: tests/lexer.o src/lexer.o
	$(CXX) $(CXXFLAGS) $^ -o $@

tests/parser_test: tests/parser.o src/lexer.o src/parser.o
	$(CXX) $(CXXFLAGS) $^ -o $@

test: test-lexer test-parser

test-lexer: tests/lexer_test
	./tests/lexer_test "$(TEST_FILE)"

test-parser: tests/parser_test
	./tests/parser_test "$(TEST_FILE)"

-include $(DEP) $(TEST_DEP)

clean:
	rm -f $(OBJ) $(DEP) $(TARGET) $(TEST_OBJ) $(TEST_DEP) $(TEST_TARGETS)

rebuild: clean all

.PHONY: all clean rebuild test test-lexer test-parser
