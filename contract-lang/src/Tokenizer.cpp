#include <compiler/Tokenizer.hpp>
#include <iostream>
#include <stddef.h>

vector<Token> Tokenizer::tokenize()
{
  if (m_size == -1)
  {
    throw "size == -1";
  }

  int len = 0;
  int row = 0;
  int col = 0;
  char *cursor = (char *)m_source;
  char *new_line = cursor;
  char *start = cursor;
  char value = *cursor;
  bool inside_string = false;
  bool inside_inline_comment = false;
  char nextChar;

  // while not end string (NULL)
  while (value != 0)
  {
    // measure token len
    len = (int)(cursor - start);
    // if we are not inside inline coment
    if (!inside_inline_comment)
    {
      // if there is not separator and is not inside string
      if ((isBlank(value) || isDelimeter(value)) && !inside_string)
      {
        // if new line found
        if (value == '\n')
        {
          row++;
          new_line = cursor + 1;
          inside_inline_comment = false;
        }

        // if len greater then 0 push token to vector
        if (len > 0)
        {
          pushToken(start, len, row, col);
        }

        // get next char after cursor
        nextChar = cursor[1];

        // if next char is also delimiter
        if (isDelimeter(value) || isDelimeter(nextChar)) // maybe ()
        {
          // if it's not '//' inline comment
          if (value != '/' && nextChar != '/')
          {
            if (!pushToken(cursor, 2, row, col))
            {
              pushToken(cursor, 1, row, col);
            }
            else
            {
              cursor++;
            }
          }
          else
          {
            // std::cout << "inline comment start\n";
            inside_inline_comment = true;
          }
        }
        else
        {
          pushToken(cursor, 1, row, col);
        }
        start = cursor + 1;
        col = (int)(cursor - new_line + 1);
      }
      else if (value == '"')
      {
        inside_string = !inside_string;
      }
      else if (inside_string && value == '\n')
      {
        Token token{TokenType::T_UNKNOWN, start, len, row, col};

        std::cout << "can't use \\n in string const.\n";
      }
    }
    else if (inside_inline_comment && value == '\n')
    {
      // std::cout << "inline commend end\n";

      inside_inline_comment = false;
      row++;
      col = 1;
      new_line = cursor + 1;
      start = cursor + 1;
      col = (int)(cursor - new_line + 1);
    }

    // increment cursor ptr
    cursor++;
    // read next char
    value = *cursor;
  }

  // if there is a last token
  // use token information
  if (inside_string)
  {
    len = (int)(cursor - start);
    Token token = {TokenType::T_UNKNOWN, start, len, row, col};

    std::cout << "string const not closed by '\"'\n";
  }

  // if there is a last token
  // push last token to vector
  if (!inside_inline_comment)
  {
    len = (int)(cursor - start);
    if (len > 0)
    {
      pushToken(start, len, row, col);
    }
  }

  return m_tokens;
};

bool Tokenizer::pushToken(char *text, int len, int row, int col)
{
  TokenType type = getTokenType(text, len);
  if (type != TokenType::T_UNKNOWN)
  {
    m_tokens.push_back({
        type,
        text,
        len,
        row,
        col,
    });

    return true;
  }

  return false;
};

TokenType Tokenizer::getTokenType(char *text, int len)
{
  if (text == NULL || len == 0)
  {
    return TokenType::T_UNKNOWN;
  }

  for (int i = 0; i < TOKEN_TYPE_COUNT; i++)
  {
    const char *m = TOKEN_TYPE_MNEMONIC[i];
    int m_len = (int)strlen(m);
    if (m_len == len && strncmp(text, m, m_len) == 0)
    {
      return (TokenType)i;
    }
  }

  if (isdigit(text[0]))
  {
    return validateNumber(text, len);
  }

  if (isalnum(text[0]) || text[0] == '_')
  {
    return validateId(text, len);
  }

  if (text[0] == '"')
  {
    return validateString(text, len);
  }

  return TokenType::T_UNKNOWN;
};

TokenType Tokenizer::validateId(char *text, int len)
{
  if (len < 1)
  {
    return TokenType::T_UNKNOWN;
  }

  for (int i = 0; i < len; i++)
  {
    if (!isalnum(text[i]) && text[i] != '_' && text[i] != '$')
      return TokenType::T_UNKNOWN;
  }

  return TokenType::T_ID;
};

TokenType Tokenizer::validateNumber(char *text, int len)
{
  if (len < 1)
  {
    return TokenType::T_UNKNOWN;
  }

  for (int i = 0; i < len; i++)
  {
    if (!isdigit(text[i]))
      return TokenType::T_UNKNOWN;
  }

  return TokenType::T_CONST_INT;
};

TokenType Tokenizer::validateString(char *text, int len)
{
  if (len < 2 || text[len - 1] != '"')
  {
    return TokenType::T_UNKNOWN;
  }

  return TokenType::T_CONST_STRING;
};
