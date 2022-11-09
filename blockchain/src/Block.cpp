#include <blockchain/Block.hpp>
#include <string>
#include <sstream>
#include <blockchain/SHA256.hpp>
#include <openssl/bn.h>
#include <blockchain/Tx.hpp>
#include <vector>

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
Block::~Block(){

};

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
const char *Block::getPrevHash()
{
  return m_prevHash;
};

////////////////////////////////////////////////////////////////////////////////
// Generate hash
// @return block hash
////////////////////////////////////////////////////////////////////////////////
char *Block::getHash()
{
  std::stringstream ss;

  ss << m_index
     << m_prevHash
     << m_timestamp;

  std::string s = ss.str();

  unsigned char dig[32];
  ::crypto::SHA256(dig, s.c_str(), s.size());

  BIGNUM *bn = BN_new();
  BN_bin2bn(dig, 32, bn);

  char *hash = BN_bn2hex(bn);

  BN_free(bn);

  return hash;
};

////////////////////////////////////////////////////////////////////////////////
// @return block index
////////////////////////////////////////////////////////////////////////////////
int Block::getIndex()
{
  return m_index;
};

////////////////////////////////////////////////////////////////////////////////
// Set block index
// @return void
////////////////////////////////////////////////////////////////////////////////
void Block::setIndex(int index)
{
  m_index = index;
};

////////////////////////////////////////////////////////////////////////////////
// @return block timestamp in unix time
////////////////////////////////////////////////////////////////////////////////
int Block::getTimestamp()
{
  return m_timestamp;
};

////////////////////////////////////////////////////////////////////////////////
// Set transactions
// @return void
////////////////////////////////////////////////////////////////////////////////
void Block::setTransactions(std::vector<Tx *> transactions)
{
  m_transactions = transactions;
};

////////////////////////////////////////////////////////////////////////////////
// @return transactions
////////////////////////////////////////////////////////////////////////////////
std::vector<Tx *> Block::getTransactions()
{
  return m_transactions;
};