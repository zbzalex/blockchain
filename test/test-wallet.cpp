#include <iostream>
#include "wallet.h"
// c style
#include <string.h>

#include <vector>
#include <string>
#include "utility.h"
#include "test.h"

bool test_wallet()
{
    Wallet wallet;
	std::vector<uint8_t> vchSalt (32);
	memset(&vchSalt[0], 0, 32);
	std::string password {"password123"};
	std::vector<uint8_t> vchPass { password.begin(), password.end() };
	if (wallet.SetKeyFromPassphrase(vchPass, vchSalt)) {
		std::cout << wallet.keyToHex() << "\n";
		std::cout << wallet.ivToHex() << "\n";

		std::vector<uint8_t> vchCipherText;

		std::string in { "hello" };
		std::vector<uint8_t> vchIn (in.begin(), in.end());
		
		if (wallet.Encrypt(vchIn, vchCipherText)) {
			std::cout << "encrypted successful!\n";

			// BIGNUM *bn = BN_new();
			// BN_bin2bn(&vchCipherText[0], vchCipherText.size(), bn);
			// std::cout << BN_bn2hex(bn) << "\n";
			
			BigNum bn( &vchCipherText[0], vchCipher.size() );
			std::cout << bn.ToHexString() << "\n";

			std::vector<uint8_t> vchOut;
			if (wallet.Decrypt(vchCipherText, vchOut)) {
				std::cout << "decrypted successful!\n";
				std::cout << (char *) vchOut.data() << "\n";
			}
		}

	}
}

int main()
{
	TEST(test_wallet);
    return 0;
}
