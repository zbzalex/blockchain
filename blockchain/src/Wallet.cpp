#include <blockchain/Wallet.hpp>
#include <iostream>
#include <cstring>
#include <openssl/ec.h>
#include <openssl/ecdsa.h>
#include <openssl/bn.h>
#include <openssl/sha.h>
#include <blockchain/SHA256.hpp>

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
Wallet::Wallet(){

};

Wallet::~Wallet(){
  EC_KEY_free(m_keyPairObj);
};

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
int Wallet::create()
{
  // generate secp256k1 key pair
  m_keyPairObj = EC_KEY_new_by_curve_name(NID_secp256k1);
  EC_KEY_generate_key(m_keyPairObj);

  // get private key
  BIGNUM *bn = (BIGNUM *)EC_KEY_get0_private_key(m_keyPairObj);
  m_hexKey = BN_bn2hex(bn);

  // get public key
  EC_POINT *pubKey = (EC_POINT *)EC_KEY_get0_public_key(m_keyPairObj);
  EC_GROUP *secp256k1Group = EC_GROUP_new_by_curve_name(NID_secp256k1);
  m_hexPubKey = EC_POINT_point2hex(secp256k1Group, pubKey, POINT_CONVERSION_UNCOMPRESSED, nullptr);

  // // final
  EC_GROUP_free(secp256k1Group);
};

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
int Wallet::createFromHex(char *hexKey)
{
  m_hexKey = hexKey;

  m_keyPairObj = EC_KEY_new_by_curve_name(NID_secp256k1);

  BIGNUM *bn = BN_new();
  BN_hex2bn(&bn, hexKey);

  EC_KEY_set_private_key(m_keyPairObj, bn);

  BN_CTX *ctx = BN_CTX_new();
  BN_CTX_start(ctx);
  const EC_GROUP *curveGroup = EC_KEY_get0_group(m_keyPairObj);
  EC_POINT *pubPoint = EC_POINT_new(curveGroup);
  EC_POINT_mul(curveGroup, pubPoint, bn, NULL, NULL, ctx);
  EC_KEY_set_public_key(m_keyPairObj, pubPoint);
  m_hexPubKey = EC_POINT_point2hex(curveGroup, pubPoint, POINT_CONVERSION_UNCOMPRESSED, nullptr);
  EC_POINT_free(pubPoint);
  BN_CTX_end(ctx);
  BN_CTX_free(ctx);

  BN_clear_free(bn);
};

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
char *Wallet::getHexKey()
{
  return m_hexKey;
};

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
char *Wallet::getHexPubKey()
{
  return m_hexPubKey;
};

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
int Wallet::sign(uint8_t **sig, int *siglen, const char *message, int len)
{

  uint8_t dig[32];
  ::crypto::SHA256(dig, message, len);

  *siglen = ECDSA_size(m_keyPairObj);
  *sig = (uint8_t *)OPENSSL_malloc(*siglen);

  ECDSA_sign(0, dig, 32, *sig, (unsigned int *)siglen, m_keyPairObj);

  return 0;
};

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
bool Wallet::verify(unsigned char *dig, const unsigned char *sig, int siglen)
{
  // m_importedKeyPairObj = EC_KEY_new_by_curve_name(NID_secp256k1);
  // EC_GROUP *curveGroup = EC_GROUP_new_by_curve_name(NID_secp256k1);
  // EC_POINT *pubPoint = EC_POINT_new(curveGroup);
  // pubPoint = EC_POINT_hex2point(curveGroup, m_hexPubKey, pubPoint, nullptr);
  // EC_KEY_set_public_key(m_importedKeyPairObj, pubPoint);
  // EC_GROUP_free(curveGroup);
  // EC_POINT_free(pubPoint);

  // BIGNUM *bn = BN_new();
  // BN_hex2bn(&bn, m_hexKey);
  // EC_KEY_set_private_key(m_importedKeyPairObj, bn);
  // BN_clear_free(bn);

  // return ECDSA_verify(0, dig, SHA256_DIGEST_LENGTH, sig, siglen, m_importedKeyPairObj) == 1;
  return ECDSA_verify(0, dig, SHA256_DIGEST_LENGTH, sig, siglen, m_keyPairObj) == 1;
};
