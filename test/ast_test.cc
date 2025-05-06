#include <gtest/gtest.h>
#include "minimal_fe.h"

TEST(ASTTest, NumberExprAST) {
  auto expr = std::make_unique<NumberExprAST>(42.0);
  ASSERT_NE(expr, nullptr);
}

TEST(ASTTest, VariableExprAST) {
  auto expr = std::make_unique<VariableExprAST>("x");
  ASSERT_NE(expr, nullptr);
}

TEST(ASTTest, BinaryExprAST) {
  auto lhs = std::make_unique<NumberExprAST>(1.0);
  auto rhs = std::make_unique<NumberExprAST>(2.0);
  auto expr = std::make_unique<BinaryExprAST>('+', std::move(lhs), std::move(rhs));
  ASSERT_NE(expr, nullptr);
}

TEST(ASTTest, CallExprAST) {
  std::vector<std::unique_ptr<ExprAST>> args;
  args.push_back(std::make_unique<NumberExprAST>(1.0));
  args.push_back(std::make_unique<NumberExprAST>(2.0));
  auto expr = std::make_unique<CallExprAST>("add", std::move(args));
  ASSERT_NE(expr, nullptr);
}

TEST(ASTTest, PrototypeAST) {
  std::vector<std::string> args = {"x", "y"};
  auto proto = std::make_unique<PrototypeAST>("add", std::move(args));
  ASSERT_NE(proto, nullptr);
  EXPECT_EQ(proto->GetName(), "add");
}

TEST(ASTTest, FunctionAST) {
  std::vector<std::string> args = {"x", "y"};
  auto proto = std::make_unique<PrototypeAST>("add", std::move(args));
  auto body = std::make_unique<BinaryExprAST>(
      '+',
      std::make_unique<VariableExprAST>("x"),
      std::make_unique<VariableExprAST>("y")
  );
  auto func = std::make_unique<FunctionAST>(std::move(proto), std::move(body));
  ASSERT_NE(func, nullptr);
}

TEST(ASTTest, ComplexExpression) {
  // Test a more complex expression: (x + y) * (a + b)
  auto expr = std::make_unique<BinaryExprAST>(
      '*',
      std::make_unique<BinaryExprAST>(
          '+',
          std::make_unique<VariableExprAST>("x"),
          std::make_unique<VariableExprAST>("y")
      ),
      std::make_unique<BinaryExprAST>(
          '+',
          std::make_unique<VariableExprAST>("a"),
          std::make_unique<VariableExprAST>("b")
      )
  );
  ASSERT_NE(expr, nullptr);
}

TEST(ASTTest, NestedFunctionCall) {
  // Test a nested function call: add(multiply(x, y), z)
  std::vector<std::unique_ptr<ExprAST>> mult_args;
  mult_args.push_back(std::make_unique<VariableExprAST>("x"));
  mult_args.push_back(std::make_unique<VariableExprAST>("y"));

  std::vector<std::unique_ptr<ExprAST>> add_args;
  add_args.push_back(std::make_unique<CallExprAST>("multiply", std::move(mult_args)));
  add_args.push_back(std::make_unique<VariableExprAST>("z"));

  auto expr = std::make_unique<CallExprAST>("add", std::move(add_args));
  ASSERT_NE(expr, nullptr);
}