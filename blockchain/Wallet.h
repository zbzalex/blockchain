#ifndef WALLET_H
#define WALLET_H

#include <openssl/aes.h>
#include <openssl/evp.h>
#include <string>
#include <inttypes.h>
#include <vector>
#include <memory>
#include <algorithm>
#include <openssl/bn.h>

// c
#include <stdlib.h>
#include <string.h>

#include <string>

//
//
//
class Wallet
{
private:
    //
    //
    //
    std::vector<uint8_t> vchKey_;

    //
    //
    //
    std::vector<uint8_t> vchIv_;

public:
    //
    //
    //
    Wallet()
    {
        vchKey_.reserve(32);
        vchIv_.reserve(32);
    }

    //
    //
    //
    bool SetKeyFromPassphrase(
        const std::vector<uint8_t> &vchPass,
        const std::vector<uint8_t> &vchSalt)
    {
        if (vchSalt.size() < 32)
            return false;

        uint8_t *chKey = (uint8_t *)malloc(32);
        uint8_t *chIv = (uint8_t *)malloc(32);

        if (EVP_BytesToKey(EVP_aes_256_cbc(), EVP_sha512(), &vchSalt[0], &vchPass[0], vchPass.size(), 1, chKey, chIv) == 0)
            return false;

        memcpy(&vchKey_[0], &chKey[0], 32);
        memcpy(&vchIv_[0],  &chIv[0],  32);

        return true;
    }

    //
    //
    //
    bool SetKey(
        std::vector<uint8_t> vchNewKey,
        std::vector<uint8_t> vchNewIv)
    {
        if (vchNewKey.size() < 32 || vchNewIv.size() < 32)
            return false;

        memcpy(&vchKey_[0], &vchNewKey[0], 32);
        memcpy(&vchIv_[0],  &vchNewIv[0],  32);

        return true;
    }

    //
    //
    //
    bool Encrypt(const std::vector<uint8_t> vchIn, std::vector<uint8_t> &vchCipherText) const
    {

        int encrypted_size = vchIn.size() + EVP_MAX_BLOCK_LENGTH;

        vchCipherText.resize(encrypted_size);

        EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();

        if (!EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, &vchKey_[0], &vchIv_[0]))
            return false;

        int len;

        if (!EVP_EncryptUpdate(ctx, &vchCipherText[0], &len, &vchIn[0], vchIn.size()))
            return false;

        encrypted_size = len;

        if (!EVP_EncryptFinal_ex(ctx, (&vchCipherText[0]) + encrypted_size, &len))
            return false;

        encrypted_size += len;

        EVP_CIPHER_CTX_free(ctx);

        vchCipherText.resize(encrypted_size);

        return true;
    }

    //
    //
    //
    bool Decrypt(const std::vector<uint8_t> &vchCipherText, std::vector<uint8_t> &vchOut) const
    {
        EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();

        if (!EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, &vchKey_[0], &vchIv_[0]))
            return false;

        int decrypted_size = vchCipherText.size() + EVP_MAX_BLOCK_LENGTH;
        // allocate memory for output byffer
        uint8_t *buf = new uint8_t[decrypted_size];

        int len;
        if (!EVP_DecryptUpdate(ctx, buf, &len, &vchCipherText[0], vchCipherText.size()))
            return false;

        decrypted_size = len;

        if (!EVP_DecryptFinal_ex(ctx, buf + len, &len))
            return false;

        decrypted_size += len;

        EVP_CIPHER_CTX_free(ctx);

        vchOut.resize(decrypted_size);

        std::copy(buf, buf + decrypted_size, vchOut.begin());

        return true;
    }

    //
    //
    //
    std::string keyToHex() const
    {
        BIGNUM *bn = BN_new();

        BN_bin2bn(&vchKey_[0], 32, bn);
        char *hex = BN_bn2hex(bn);

        return hex;
    }

    //
    //
    //
    std::string ivToHex() const
    {
        BIGNUM *bn = BN_new();

        BN_bin2bn(&vchIv_[0], 32, bn);
        char *hex = BN_bn2hex(bn);

        return hex;
    }

    //
    //
    //
    void clear()
    {
        memset(&vchKey_[0], 0, 32);
        memset(&vchIv_[0],  0, 32);
    }
};

#endif // WALLET_H
