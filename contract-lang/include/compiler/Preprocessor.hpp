#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include <vector>
#include <compiler/Token.hpp>

using namespace std;

struct env
{
  char *root;
};

class Preprocessor
{
private:
  vector<Token> m_tokens{};
  int m_current_token;

public:
  Preprocessor(vector<Token> tokens) : m_tokens(tokens), m_current_token(0) {}

  vector<Token> process(struct env *env);

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
};

#endif
