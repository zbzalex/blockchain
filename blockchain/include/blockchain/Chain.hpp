#ifndef CHAIN_H
#define CHAIN_H

#include <blockchain/Tx.hpp>
#include <vector>
#include <blockchain/Block.hpp>

class Chain
{
private:
  std::vector<Tx *> m_transactions;
  std::vector<Block *> m_blocks;
public:
  Chain();
  ~Chain();
  bool addToPending(Tx *tx);
  std::vector<Tx*> getPendingTransactions();
  void addBlock(Block *block);
  std::vector<Block *> getBlocks();
  Block *getLastBlock();
  Block *newBlock();
};

#endif