#ifndef WALLET_H
#define WALLET_H

#include <openssl/bn.h>
#include <openssl/ec.h>
#include <openssl/obj_mac.h>
#include <openssl/ecdsa.h>

class Wallet
{
private:
  EC_KEY *m_keyPairObj;
  //EC_KEY *m_importedKeyPairObj;
  char *m_hexKey;
  char *m_hexPubKey;

public:
  explicit Wallet();
  virtual ~Wallet();
  int create();
  int createFromHex(char *privKey);
  int sign(uint8_t **sig, int *siglen, const char *message, int len);
  bool verify(uint8_t *dig, const uint8_t *sig, int siglen);
  char *getHexKey();
  char *getHexPubKey();
};

#endif