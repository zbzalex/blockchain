#include <compiler/Preprocessor.hpp>
#include <compiler/Tokenizer.hpp>
#include <map>

vector<Token> Preprocessor::process(struct env *env)
{
  vector<Token> tokens;
  do
  {
    if (getToken().type == TokenType::T_INCLUDE && getNextToken().type == TokenType::T_CONST_STRING)
    {
      Token token = getNextToken();
      char *includePath = token.getText();
      int newlen = strlen(includePath) - 2;
      char *absolutePath = (char *)malloc(newlen);
      memcpy(absolutePath, includePath + 1, newlen);

      int size = strlen(env->root) + strlen(absolutePath) + 1;
      absolutePath = (char *)malloc(size);
      memset(absolutePath, 0, size);
      memcpy(absolutePath, env->root, strlen(env->root));
      memcpy(absolutePath + strlen(env->root), includePath + 1, newlen);

      Tokenizer tokenizer;
      if (tokenizer.load(absolutePath) == EXIT_SUCCESS)
      {
        vector<Token> include_file_tokens = tokenizer.tokenize();
        Preprocessor preprocessor{include_file_tokens};
        vector<Token> include_tokens = preprocessor.process(env);
        tokens.insert(tokens.end(), include_tokens.begin(), include_tokens.end());
      }
    }
  } while (next());

  tokens.insert(tokens.end(), m_tokens.begin(), m_tokens.end());

  return tokens;
};
