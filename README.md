# Mini Front End LLVM

A simple front end for LLVM IR.
Mainly for educational and benchmarking purposes.
Aiming to impliment this in <= 1000 lines of code.

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

The project uses Google Test for unit testing. To build and run the tests:

```bash
# Create a build directory
mkdir build && cd build

# Configure with CMake
cmake ..

# Build
make

# Run tests
ctest
```

Or run the test executable directly:
```bash
./minimal_fe_test
```
