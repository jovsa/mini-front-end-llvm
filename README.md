# Mini Front End LLVM

A simple front end for LLVM IR.
Mainly for educational and benchmarking purposes.
Aiming to impliment this in <= 1000 lines of code.

[![Tests](https://github.com/jovan.sardinha/mini-front-end-llvm/actions/workflows/tests.yml/badge.svg)](https://github.com/jovan.sardinha/mini-front-end-llvm/actions/workflows/tests.yml)

## Building and Running

## Version History

### V1: A Minimal Frontend

To compile and run the minimal frontend:
```bash
clang++ -std=c++14 -g -O3 src/minimal_fe.cpp && ./a.out
```

The program accepts various inputs:
- Numbers (e.g., `4.5`)
- Binary operations (e.g., `1 + 2`)
- Function definitions (e.g., `def add(x y) x + y`)
- Function calls (e.g., `add(1, 2)`)

Press Ctrl+C to exit the program.

### Features
1. A simple lexer
2. A basic parser
3. Abstract Syntax Tree (AST)
4. A driver loop


## Running Tests

The project uses Google Test for unit testing. To run the tests:

```bash
./build/minimal_fe_test
```

Or to build and run in one command:
```bash
mkdir -p build && cd build && cmake .. && make && ./minimal_fe_test
```

## Continuous Integration

The project uses GitHub Actions to run tests on every push to main and pull requests. The tests are run with both GCC and Clang compilers to ensure compatibility.
