#include <compiler/Parser.hpp>
#include <iostream>
#include <compiler/Tokenizer.hpp>
#include <stddef.h>
#include <compiler/Scope.hpp>

void Parser::parse()
{
  Scope *globalScope = new Scope("global");

  do
  {
    if (isPrimitiveType(getToken().type) && getNextToken().type == TokenType::T_ID && getNextNextToken().type == TokenType::T_OP_PARENTHESES)
    {
      next();
      char *function_name = getToken().getText();
      std::cout << "decl function = " << function_name << "\n";
      next(); // (
      next(); // )
      next(); // {
      do
      {
        if (getToken().type == TokenType::T_CL_BRACES)
        { // }
          break;
        }
      } while (next());
    }
  } while (next());
};
