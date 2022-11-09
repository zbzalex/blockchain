#ifndef BLOCK_H
#define BLOCK_H

#include <time.h>
#include <vector>
#include <blockchain/Tx.hpp>

class Block
{
private:
  int m_index;
  const char *m_prevHash;
  int m_timestamp;
  std::vector<Tx *> m_transactions;

public:
  Block(const char *prevHash) : m_prevHash(prevHash)
  {
    m_timestamp = time(NULL);
  };
  ~Block();
  int getIndex();
  void setIndex(int index);
  const char *getPrevHash();
  char *getHash();
  int getTimestamp();
  void setTransactions(std::vector<Tx *> transactions);
  std::vector<Tx *> getTransactions();
};

#endif