#ifndef SHA256_H
#define SHA256_H

#include <openssl/sha.h>

namespace crypto
{
  static int SHA256(unsigned char *digest, const char *message, unsigned int len)
  {
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, message, len);
    SHA256_Final(digest, &ctx);
    return 0;
  }
};

#endif