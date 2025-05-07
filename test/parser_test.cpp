#include <gtest/gtest.h>
#include "minimal_fe.h"
#include <cstdio>
#include <sstream>
#include <string>

class ParserTest : public ::testing::Test {
 protected:
  void SetUp() override {
    // Save original stdin
    original_stdin = stdin;
    // Initialize operator precedence
    BinopPrecedence['<'] = 10;
    BinopPrecedence['+'] = 20;
    BinopPrecedence['-'] = 20;
    BinopPrecedence['*'] = 40;
  }

  void TearDown() override {
    // Restore original stdin
    if (temp_file) {
      fclose(temp_file);
    }
    stdin = original_stdin;
  }

  void SetInput(const std::string& input) {
    // Close previous temp file if it exists
    if (temp_file) {
      fclose(temp_file);
    }

    // Create a temporary file for input
    temp_file = tmpfile();
    fputs(input.c_str(), temp_file);
    fflush(temp_file);
    rewind(temp_file);
    stdin = temp_file;

    // Reset lexer state
    ResetLexer();
    getNextToken(); // Prime the parser
  }

  FILE* original_stdin;
  FILE* temp_file = nullptr;
};

TEST_F(ParserTest, ParseNumber) {
  SetInput("123.45");
  auto expr = ParseNumberExpr();
  ASSERT_NE(expr, nullptr);
}

TEST_F(ParserTest, ParseIdentifier) {
  SetInput("abc");
  auto expr = ParseIdentifierExpr();
  ASSERT_NE(expr, nullptr);
}

TEST_F(ParserTest, ParseBinaryOp) {
  SetInput("1 + 2");
  auto expr = ParseExpression();
  ASSERT_NE(expr, nullptr);
}

TEST_F(ParserTest, ParseParenExpr) {
  SetInput("(1 + 2)");
  auto expr = ParseParenExpr();
  ASSERT_NE(expr, nullptr);
}

TEST_F(ParserTest, ParseFunctionDef) {
  SetInput("def add(x y) x + y");
  auto func = ParseDefinition();
  ASSERT_NE(func, nullptr);
}

TEST_F(ParserTest, ParseExtern) {
  SetInput("extern sin(x)");
  auto proto = ParseExtern();
  ASSERT_NE(proto, nullptr);
}

TEST_F(ParserTest, ParseFunctionCall) {
  SetInput("add(1, 2)");
  auto expr = ParseIdentifierExpr();
  ASSERT_NE(expr, nullptr);
}

TEST_F(ParserTest, ParseTopLevelExpr) {
  SetInput("1 + 2 * 3");
  auto func = ParseTopLevelExpr();
  ASSERT_NE(func, nullptr);
}

TEST_F(ParserTest, InvalidExpr) {
  SetInput(")");
  auto expr = ParseExpression();
  EXPECT_EQ(expr, nullptr);
}

TEST_F(ParserTest, InvalidFunctionDef) {
  SetInput("def add(x y");
  auto func = ParseDefinition();
  EXPECT_EQ(func, nullptr);
}