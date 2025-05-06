#include <gtest/gtest.h>
#include "minimal_fe.h"
#include <cstdio>
#include <sstream>
#include <string>

// Mock stdin for testing
class LexerTest : public ::testing::Test {
 protected:
  void SetUp() override {
    // Save original stdin
    original_stdin = stdin;
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
  }

  FILE* original_stdin;
  FILE* temp_file = nullptr;
};

TEST_F(LexerTest, NumberToken) {
  SetInput("123.45");
  EXPECT_EQ(gettok(), tok_number);
  EXPECT_DOUBLE_EQ(NumVal, 123.45);
}

TEST_F(LexerTest, IdentifierToken) {
  SetInput("abc");
  EXPECT_EQ(gettok(), tok_identifier);
  EXPECT_EQ(IdentifierStr, "abc");
}

TEST_F(LexerTest, DefKeyword) {
  SetInput("def");
  EXPECT_EQ(gettok(), tok_def);
}

TEST_F(LexerTest, ExternKeyword) {
  SetInput("extern");
  EXPECT_EQ(gettok(), tok_extern);
}

TEST_F(LexerTest, BinaryOperator) {
  SetInput("+");
  EXPECT_EQ(gettok(), '+');
}

TEST_F(LexerTest, Parens) {
  SetInput("()");
  EXPECT_EQ(gettok(), '(');
  EXPECT_EQ(gettok(), ')');
}

TEST_F(LexerTest, Whitespace) {
  SetInput("  \t\n  123");
  EXPECT_EQ(gettok(), tok_number);
  EXPECT_DOUBLE_EQ(NumVal, 123);
}

TEST_F(LexerTest, Comment) {
  SetInput("# This is a comment\n123");
  EXPECT_EQ(gettok(), tok_number);
  EXPECT_DOUBLE_EQ(NumVal, 123);
}

TEST_F(LexerTest, EndOfFile) {
  SetInput("");
  EXPECT_EQ(gettok(), tok_eof);
}