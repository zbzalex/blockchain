#ifndef TOKEN_H
#define TOKEN_H

#include <stdlib.h>
#include <memory.h>

enum class TokenType
{
  T_UNKNOWN = 0,
  T_ID,
  T_COMMA,
  T_SEMI,
  T_OP_BRACES,
  T_CL_BRACES,
  T_OP_BRACKETS,
  T_CL_BRACKETS,
  T_OP_PARENTHESES,
  T_CL_PARENTHESES,
  T_INT,
  T_IF,
  T_ELSE,
  T_WHILE,
  T_RETURN,
  T_BREAK,
  T_ASSIGN,
  T_PLUS,
  T_MINUS,
  T_MUL,
  T_DIV,
  T_EQ,
  T_NOT_EQ,
  T_GT,
  T_GTE,
  T_LT,
  T_LTE,
  T_LOGIC_AND,
  T_LOGIC_OR,
  T_LOGIC_NOT,
  T_VOID,
  T_BOOL,
  T_BOOLTRUE,
  T_BOOLFALSE,
  T_STRING,
  T_CONST_INT,
  T_CONST_STRING,
  T_INCLUDE,
};

constexpr char *const TOKEN_TYPE_MNEMONIC[] = {
    "",  // T_UNKNOWN
    "",  // T_ID
    ",", // T_COMMA
    ";", // T_SEMI
    "{",
    "}",
    "[",
    "]",
    "(",
    ")",
    "int",
    "if",
    "else",
    "while",
    "return",
    "break",
    "=", // T_ASSIGN
    "+", // T_PLUS
    "-",
    "*",
    "/",
    "==",
    "!=",
    ">",
    ">=",
    "<",
    "<=",
    "&&",
    "||",
    "!",
    "void",     // T_VOID
    "bool",     // T_BOOL
    "true",     // T_BOOLTRUE
    "false",    // T_BOOLFALSE
    "string",   // T_STRING
    "",         // T_CONST_INT
    "",         // T_CONST_STRING
    "include",  // T_INCLUDE
};

constexpr int TOKEN_TYPE_COUNT = sizeof(TOKEN_TYPE_MNEMONIC) / sizeof(char *);

struct Token
{
  TokenType type;
  char *text;
  int len;
  int row;
  int col;

  char *getText() {
    char *__text = (char*)malloc(len+1);
    __text[len]=0;
    memcpy(__text, text, len);

    return __text;
  }
};

#endif
