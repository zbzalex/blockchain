#ifndef BLOCK_H
#define BLOCK_H

class Block
{
private:
  int m_index;
  char *m_prevHash;

public:
  Block();
  ~Block();
  char *getPrevHash();
  char *getHash();
};

#endif