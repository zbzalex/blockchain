#ifndef TX_H
#define TX_H

#include <time.h>

class Tx
{
private:
  int m_index;
  const char *m_from;
  const char *m_to;
  int m_amount;
  int m_timestamp;

public:
  Tx(const char *from, const char *to, int amount): m_from(from), m_to(to), m_amount(amount)
  {

    m_timestamp = time(NULL);
  };

  ~Tx();
  void setIndex(int index);
  int getIndex();
  char *getHash();
  const char *getFrom();
  const char *getTo();
  int getAmount();
  int getTimestamp();
};

#endif