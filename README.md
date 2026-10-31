# C-compiler

A C compiler written in C++ for fun and to learn how compilers work.

The project is in early development. Hoping to make it replicate a c stadard at
some point.

## Requirements

- A C++20 compiler (`clang++` is the default in the Makefile).
- `make`.

The project uses the C++ standard library and has no external library dependencies.

## Building

From the project directory, run:

```sh
make
```

This builds the `compiler` executable in the project directory. To use another
C++20 compiler, override `CXX`:

```sh
make CXX=g++
```

Other build commands:

```sh
make clean    # Remove the executable, object files, and generated dependency files
make rebuild  # Clean and rebuild the project
```

## Running tests

The test programs read a C source file and print the tokens or parsed syntax tree
for inspection. They return a nonzero exit code if lexing or parsing fails; they
do not compare the output against an expected result.

```sh
make test         # Build and run both tests using tests/sample.c
make test-lexer   # Print the tokens
make test-parser  # Print the abstract syntax tree
```

To use your own source file:

```sh
make test TEST_FILE=test.c
make test-parser TEST_FILE=path/to/source.c
```

`make clean` also removes the test executables and their build files.
