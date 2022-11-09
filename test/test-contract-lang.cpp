#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <compiler/Tokenizer.hpp>
#include <compiler/Parser.hpp>
#include <compiler/Preprocessor.hpp>
#include <unistd.h>
#include <memory.h>

using namespace std;

int main(int argc, char *argv[])
{
  struct env *env;
  env->root = (char *) malloc(255);
  memset(env->root, 0, 255);
  getcwd(env->root, 255);
  memcpy(env->root + strlen(env->root), "/../test/", 9);

  Tokenizer tokenizer;
  if (tokenizer.load("../test/test.contract") == EXIT_SUCCESS)
  {
    vector<Token> tokens = tokenizer.tokenize();
    Preprocessor preprocessor{tokens};
    tokens = preprocessor.process(env);
    Parser parser{tokens};
    parser.parse();
  }

  return 0;
}
