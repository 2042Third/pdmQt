//
// Created by 18604 on 2/14/2023.
//

#ifndef PDM_QT_PARSER_H
#define PDM_QT_PARSER_H
#include <iostream>
#include <vector>
#include <string>
#include <stack>

enum class NodeType {
  Program,
  FunctionDeclaration,
  VariableDeclaration,
  Expression,
};

struct Node {
  NodeType type;
  std::string value;
  std::vector<Node> children;
};

class Parser {
public:
  Parser(const std::string &input)
      : input_(input),
        pos_(0)
  {
  }

  Node parse() {
    Node program;
    program.type = NodeType::Program;
    while (pos_ < input_.length()) {
      Node declaration = parseDeclaration();
      program.children.push_back(declaration);
    }
    return program;
  }

private:
  std::string input_;
  std::size_t pos_;
  Node parseDeclaration() {
    if (lookahead("int")) {
      Node declaration;
      declaration.type = NodeType::FunctionDeclaration;
      nextToken();
      declaration.value = parseIdentifier();
      nextToken();
      nextToken();
      while (!lookahead(")")) {
        Node parameter = parseDeclaration();
        declaration.children.push_back(parameter);
      }
      nextToken();
      declaration.children.push_back(parseBlock());
      return declaration;
    } else {
      Node declaration;
      declaration.type = NodeType::VariableDeclaration;
      declaration.value = parseIdentifier();
      nextToken();
      if (lookahead("=")) {
        nextToken();
        declaration.children.push_back(parseExpression());
      }
      nextToken();
      return declaration;
    }
  }

  Node parseBlock() {
    Node block;
    block.type = NodeType::Expression;
    nextToken();
    while (!lookahead("}")) {
      Node statement = parseDeclaration();
      block.children.push_back(statement);
    }
    nextToken();
    return block;
  }

  Node parseExpression() {
    Node expression;
    expression.type = NodeType::Expression;
    expression.value = parseIdentifier();
    if (lookahead("(")) {
      nextToken();
      while (!lookahead(")")) {
        Node argument = parseExpression();
        expression.children.push_back(argument);
      }
      nextToken();
    }
    return expression;
  }

  std::string parseIdentifier() {
    std::string identifier;
    while (std::isalpha(input_[pos_]) || std::isdigit(input_[pos_])) {
      identifier += input_[pos_++];
    }
    return identifier;
  }

  bool lookahead(const std::string &token) {
    std::size_t pos = pos_;
    for (char c : token) {
      if (input_[pos++] != c) {
        return false;
      }
    }
    return true;
  }

  void nextToken() {
    while (std::isspace(input_[pos_])) {
      ++pos_;
    }
  }


};

#endif //PDM_QT_PARSER_H
