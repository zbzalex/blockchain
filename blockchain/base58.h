#ifndef BASE58_H
#define BASE58_H

#include <vector>
#include <iostream>
#include <string>
#include <openssl/bn.h>
#include <openssl/types.h>
#include <algorithm>
#include <exception>

static const char* base58_alphabet = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";

std::string base58_encode(unsigned char *pbegin, unsigned char *pend)
{
    int size = pend - pbegin;

    std::vector<uint8_t> vchTmp(size + 1, 0);
    std::reverse_copy(pbegin, pend, vchTmp.begin());

    BIGNUM *bn = BN_new();
    std::vector<uint8_t> vch2(vchTmp.size() + 4);
    unsigned int nSize = vchTmp.size();
    
    // put 4 bytes
    vch2[0] = (nSize >> 24) & 0xff;
    vch2[1] = (nSize >> 16) & 0xff;
    vch2[2] = (nSize >> 8)  & 0xff;
    vch2[3] = (nSize >> 0)  & 0xff;
    
    std::reverse_copy(vchTmp.begin(), vchTmp.end(), vch2.begin() + 4);
    BN_mpi2bn(&vch2[0], vch2.size(), bn);

    BN_CTX *pctx = BN_CTX_new();
    BIGNUM *bn58 = BN_new();
    BN_set_word(bn58, 58);

    BIGNUM *bn0     = BN_new();
    BN_set_word(bn0,   0);

    std::string str;
    str.reserve(size * 138 / 100 + 1);
    
    BIGNUM *dv  = BN_new();
    BIGNUM *rem = BN_new();

    while( BN_cmp(bn, bn0) > 0 )
    {
        if (!BN_div(dv, rem, bn, bn58, pctx))
            throw std::runtime_error("BN_div failed");

        BN_swap(bn, dv);
        
        unsigned long c = BN_get_word(rem);

        str += base58_alphabet[c];
    }

    for (
        const unsigned char* p = pbegin;
        p < pend && *p == 0;
        p++
    )
    {
        str += base58_alphabet[0];
    }

    std::reverse(str.begin(), str.end());

    return str;
}

std::vector<uint8_t> base58_decode(const std::string &encoded)
{
    // vector to return
    std::vector<uint8_t> vch;
    
    BN_CTX *pctx = BN_CTX_new();

    // 58
    BIGNUM *bn58 = BN_new();
    BN_set_word(bn58, 58);

    // 0
    BIGNUM *bn = BN_new();
    BN_set_word(bn,    0);

    BIGNUM * bnChar = BN_new();

    // skip spaces
    const char *s = encoded.c_str();
    while (isspace(*s))
        s++;

    for (const char* p = s; *p; p++)
    {
        const char* p1 = strchr(base58_alphabet, *p);
        if (p1 == NULL)
        {
            // skip spaces
            while (isspace(*p))
                p++;
            
            // unknown symbol
            if (*p != '\0')
                throw std::runtime_error("something wrong");
            
            break;
        }
        
        // set symbol to bn char
        BN_set_word(bnChar, p1 - base58_alphabet);

        if (!BN_mul(bn, bn, bn58, pctx))
            throw std::runtime_error("BN_mul failed");
        
        BN_add(bn, bn, bnChar);
    }

    int vchTmpSize = BN_bn2mpi(bn, NULL);

    std::vector<uint8_t> vchTmp (vchTmpSize);
    BN_bn2mpi(bn, &vchTmp[0]);

    // erase 4 bytes
    vchTmp.erase(vchTmp.begin(), vchTmp.begin() + 4);

    std::reverse(vchTmp.begin(), vchTmp.end());
    
    if (vchTmp.size() >= 2 && vchTmp.end()[-1] == 0 && vchTmp.end()[-2] >= 0x80)
        vchTmp.erase(vchTmp.end()-1);

    int nLeadingZeros = 0;
    for (const char* p = s; *p == base58_alphabet[0]; p++)
        nLeadingZeros++;

    vch.assign(nLeadingZeros + vchTmp.size(), 0);

    std::reverse_copy(vchTmp.begin(), vchTmp.end(), vch.end() - vchTmp.size());

    return vch;
}

#endif // BASE58_H