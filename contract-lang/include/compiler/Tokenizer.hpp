#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <vector>
#include <compiler/Token.hpp>
#include <iostream>

using namespace std;

constexpr char *BLANKS = (char *)"\x20\n\r\t";
constexpr char *DELIMETERS = (char *)",;{}[]()=><+-*/&|~^!";

/// @brief
/// @param filename
/// @return
static int filesize(const char *filename)
{
  FILE *fd = fopen(filename, "r");
  if (fd != NULL)
  {
    fseek(fd, 0, SEEK_END);
    int len = ftell(fd);
    fclose(fd);
    return len;
  }

  return -1;
}

/// @brief
/// @param filename
/// @param buf
/// @param fsize
static void readfile(const char *filename, char *buf, int fsize)
{
  FILE *fd = fopen(filename, "r");
  if (fd != NULL)
  {
    fseek(fd, 0, SEEK_END);
    fread(buf, fsize, 1, fd);
    fclose(fd);
  }
};

class Tokenizer
{
private:
  int m_size;
  char *m_source;
  vector<Token> m_tokens;

public:
  int load(const char *filename)
  {
    m_size = filesize(filename);
    if (m_size > 0)
    {
      char *buf = (char *)malloc(m_size);
      readfile(filename, buf, m_size);
      m_source = (char *)malloc(m_size);
      memcpy(m_source, buf, m_size);
      return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
  };

  void clear()
  {
    m_tokens.clear();
  }

  virtual vector<Token> tokenize();
  bool isBlank(char value)
  {
    return strchr(BLANKS, value) != NULL;
  };
  bool isDelimeter(char value)
  {
    return strchr(DELIMETERS, value) != NULL;
  };
  virtual bool pushToken(char *text, int len, int row, int col);
  virtual TokenType getTokenType(char *text, int len);
  virtual TokenType validateId(char *text, int len);
  virtual TokenType validateNumber(char *text, int len);
  virtual TokenType validateString(char *text, int len);
  inline int getTokenCount()
  {
    return m_tokens.size();
  }

  void debugPrint()
  {
    for (auto it = m_tokens.begin(); it != m_tokens.end(); it++)
    {
      std::cout << (int)it->type << "\t" << it->getText() << "\n";
    }
  }
};

#endif
