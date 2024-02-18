#ifndef UTILITY_H
#define UTILITY_H

#include <inttypes.h>
#include <string>
#include <openssl/bn.h>

/**
 * Big number class
 */
class BigNum : public std::vector<uint8_t> {
	private:
		BIGNUM *bn_;
	public:
		BigNum(uint8_t *bytes, int size)
		{
			bn_ = BN_new();
			BN_bin2bn(bytes, size, bn_);
		}

		~BigNum()
		{
			BN_free(bn_);
		}

		std::string ToHexString() {
			char * hex = BN_bn2hex(bn_);
			return hex;
		}
};

#endif
