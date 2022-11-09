#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <string.h>
#include <vector>
#include <compiler/Token.hpp>

using namespace std;

class Parser
{
private:
  vector<Token> m_tokens{};
  int m_current_token;

public:
  Parser(vector<Token> tokens) : m_tokens(tokens), m_current_token(0){};
  virtual void parse();
  inline int getTokenCount()
  {
    return m_tokens.size();
  }
  bool next()
  {
    m_current_token++;

    return m_current_token < getTokenCount();
  }
  void reset()
  {
    m_current_token = 0;
  }
  Token &lookupToken(int index)
  {
    return m_tokens[index];
  }
  inline Token getToken() { return lookupToken(m_current_token); };
  inline Token getNextToken() { return lookupToken(m_current_token + 1); };
  inline Token getNextNextToken() { return lookupToken(m_current_token + 2); };
  inline bool is(TokenType type) { return getToken().type == type; };

  static bool isPrimitiveType(TokenType type)
  {
    return type == TokenType::T_VOID || type == TokenType::T_INT || type == TokenType::T_STRING || type == TokenType::T_BOOL;
  }

  char *getTokenText()
  {
    Token token = getToken();
    char *text = (char *)malloc(token.len + 1);
    text[token.len] = 0;
    memcpy(text, token.text, token.len);

    return text;
  }

  TokenType getTokenType() { return getToken().type; }
};

#endif
