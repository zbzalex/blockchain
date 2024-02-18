#ifndef KEY_H
#define KEY_H

#include <openssl/bn.h>
#include <openssl/types.h>
#include <openssl/obj_mac.h>
#include <openssl/ec.h>
#include <openssl/ecdsa.h>
#include <openssl/evp.h>
#include <openssl/sha.h>
#include <vector>
#include <stdexcept>
#include <inttypes.h>
#include <openssl/ripemd.h>
#include "base58.h"

/**
 * Key class
 */
class Key
{
protected:
    EC_KEY *pkey;
    bool is_set;
public:
    Key()
    {
        pkey = EC_KEY_new_by_curve_name(NID_secp256k1);
        is_set = false;
    }

    Key(const Key &key)
    {
        pkey = EC_KEY_dup(key.pkey);
    }
	
    Key(const Key&&key);

    Key &operator=(const Key &key)
    {
        EC_KEY_copy(pkey, key.pkey);
        is_set = key.is_set;
    }

    Key &operator=(const Key&&key);

    ~Key()
    {
        EC_KEY_free(pkey);
    }

    /**
     * Checks if private key was set
     */
    bool IsNull() const
    {
        return is_set == false;
    }

    /**
     * Makes new private key
     */
    void MakeNewKey()
    {
        EC_KEY_generate_key(pkey);
        is_set = true;
    }
    
    /**
     * Set private key
     */
    bool SetPrivateKey(const std::vector<uint8_t> &vch)
    {
        const uint8_t *pbegin = &vch[0];
        return d2i_ECPrivateKey(&pkey, &pbegin, vch.size());
    }

    /**
     * Returns private key
     */
    std::vector<unsigned char> GetPrivateKey() const
    {
        unsigned int size = i2d_ECPrivateKey(pkey, NULL);
        std::vector<unsigned char> vch(size, 0);
        uint8_t *pbegin = &vch[0];
        i2d_ECPrivateKey(pkey, &pbegin);

        return vch;
    }
	
    /**
     * Set public key from uint8_t vector
     */
    bool SetPublicKey(const std::vector<uint8_t> &vch);

    /**
     * Returns public key
     */
    std::vector<uint8_t> GetPublicKey()
    {
        unsigned int size = i2o_ECPublicKey(pkey, NULL);
        
	std::vector<uint8_t> vch(size, 0);
        uint8_t *pbegin = &vch[0];
        i2o_ECPublicKey(pkey, &pbegin);

        return vch;
    }

    /**
     * Returns address from public key in base58
     */
    std::string GetAddress()
    {
        std::vector<uint8_t> vchPublicKey = GetPublicKey();

        uint8_t *pbegin = &vchPublicKey[0];
        uint8_t hash1[SHA256_DIGEST_LENGTH];
        SHA256(pbegin, vchPublicKey.size(), &hash1[0]);

        uint8_t hash2[RIPEMD160_DIGEST_LENGTH];
        RIPEMD160(&hash1[0], SHA256_DIGEST_LENGTH, hash2);

        return base58_encode(&hash2[0], &hash2[0] + RIPEMD160_DIGEST_LENGTH);
    }

    /**
     * Creates signature from digest. Digest is an message (maybe string) that
     * represents as uint8_t vector (or bytes).
     */
    std::vector<uint8_t> Sign(std::vector<uint8_t> vchDgst)
    {
        uint8_t *pch = (uint8_t *)std::malloc(4096); // 4kb max

        std::vector<uint8_t> vchSig;
        unsigned int size = 0;

        if (!ECDSA_sign(0, &vchDgst[0], vchDgst.size(), pch, &size, pkey))
            return std::vector<uint8_t>();

        std::copy(&pch[0], &pch[0] + size, std::back_inserter(vchSig));

        return vchSig;
    }

    /**
     * Verify signature
     */
    bool Verify(std::vector<uint8_t> vchDgst, std::vector<uint8_t> vchSig)
    {
        if (ECDSA_verify(0, &vchDgst[0], vchDgst.size(), &vchSig[0], vchSig.size(), pkey) != 1)
            return false;

        return true;
    }
};

#endif // KEY_H

