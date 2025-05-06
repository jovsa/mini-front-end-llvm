#ifndef SRC_MINIMAL_FE_H_
#define SRC_MINIMAL_FE_H_

#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

// Token enumeration for lexer
enum Token {
  tok_eof = -1,
  tok_def = -2,
  tok_extern = -3,
  tok_identifier = -4,
  tok_number = -5
};

// Abstract Syntax Tree (AST) class declarations
class ExprAST {
 public:
  virtual ~ExprAST() = default;
};

class NumberExprAST : public ExprAST {
  double val_;
 public:
  explicit NumberExprAST(double val) : val_(val) {}
};

class VariableExprAST : public ExprAST {
  std::string name_;
 public:
  explicit VariableExprAST(const std::string &name) : name_(name) {}
};

class BinaryExprAST : public ExprAST {
  char op_;
  std::unique_ptr<ExprAST> lhs_, rhs_;
 public:
  BinaryExprAST(char op, std::unique_ptr<ExprAST> lhs,
                std::unique_ptr<ExprAST> rhs)
      : op_(op), lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}
};

class CallExprAST : public ExprAST {
  std::string callee_;
  std::vector<std::unique_ptr<ExprAST>> args_;
 public:
  CallExprAST(const std::string &callee,
              std::vector<std::unique_ptr<ExprAST>> args)
      : callee_(callee), args_(std::move(args)) {}
};

class PrototypeAST {
  std::string name_;
  std::vector<std::string> args_;
 public:
  PrototypeAST(const std::string &name, std::vector<std::string> args)
      : name_(name), args_(std::move(args)) {}
  const std::string &GetName() const { return name_; }
};

class FunctionAST {
  std::unique_ptr<PrototypeAST> proto_;
  std::unique_ptr<ExprAST> body_;
 public:
  FunctionAST(std::unique_ptr<PrototypeAST> proto,
              std::unique_ptr<ExprAST> body)
      : proto_(std::move(proto)), body_(std::move(body)) {}
};

// Lexer interface
extern std::string IdentifierStr;
extern double NumVal;
extern int LastChar;
void ResetLexer();
int gettok();

// Parser interface
extern std::map<char, int> BinopPrecedence;
int GetTokPrecedence();
std::unique_ptr<ExprAST> LogError(const char *Str);
std::unique_ptr<PrototypeAST> LogErrorP(const char *Str);

// Parser function declarations
int getNextToken();
std::unique_ptr<ExprAST> ParseNumberExpr();
std::unique_ptr<ExprAST> ParseParenExpr();
std::unique_ptr<ExprAST> ParseIdentifierExpr();
std::unique_ptr<ExprAST> ParsePrimary();
std::unique_ptr<ExprAST> ParseBinOpRHS(int ExprPrec, std::unique_ptr<ExprAST> LHS);
std::unique_ptr<ExprAST> ParseExpression();
std::unique_ptr<PrototypeAST> ParsePrototype();
std::unique_ptr<FunctionAST> ParseDefinition();
std::unique_ptr<PrototypeAST> ParseExtern();
std::unique_ptr<FunctionAST> ParseTopLevelExpr();

// Main driver
void MainLoop();

#endif  // SRC_MINIMAL_FE_H_