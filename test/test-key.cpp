#include <iostream>
#include "Key.h"
#include <vector>
#include <string>
#include <exception>
#include "base58.h"
#include "test.h"

bool test_key()
{
	Key *pKey = new Key();
	// pKey->MakeNewKey();
	
	// std::vector<uint8_t> vPrivateKey = pKey->GetPrivateKey();
	// std::string sPrivateKey = base58_encode(
	// 	&vPrivateKey[0],
	// 	&vPrivateKey[0] + vPrivateKey.size()
	// );

	// std::cout << "private key = " << sPrivateKey << "\n";

	std::string strPrivateKey {
		"Lzhp9LopCM58wtH611RZJHjNEtTArMiDjhe45DSC11n4N92sisfLAQNTB5QvZez3TvgFd7coW7PsrRsqrKLkjXjoH1GeEaC3uEkNnYPuHfZQTmk7GmNiFza8B8s1x43ATmxJK2iog8VtdU1fzK1Ca5rmkPKGZVHYD"
	};
	
	std::vector<uint8_t> vchPrivateKey = base58_decode(strPrivateKey);

	// std::cout << base58_encode(&vchPrivateKey[0], &vchPrivateKey[0] + vchPrivateKey.size()) << "\n";
	
	if (!pKey->SetPrivateKey(vchPrivateKey))
		throw std::runtime_error("unable to set private key");

	std::vector<uint8_t> vchPublicKey = pKey->GetPublicKey();
	std::cout << base58_encode(&vchPublicKey[0], &vchPublicKey[0] + vchPublicKey.size()) << "\n";

	//std::string pubKey {
	//	"PsRTmBtk9xqddpkPdddAW8n4BG5UxXyd7bvCSFeVTVG1bL1p2M6NZiy6dFYmzoiwZJ7xhHthkdEioLguwU9ZUFtM"
	//};

	std::string addr = pKey->GetAddress();

	std::cout << addr << "\n";

	std::vector<uint8_t> vchAddr = base58_decode(addr);
	std::cout << base58_encode(
		&vchAddr[0],
		&vchAddr[0] + vchAddr.size()
	) << "\n";
	
	// raw message
	std::string msg = "Hello";
	uint8_t *pbegin = (unsigned char*) &msg[0];

	// digest
	uint8_t dgst[SHA256_DIGEST_LENGTH];
	SHA256(pbegin, msg.length(), dgst);

	// std::cout << base58_encode(&dgst[0], &dgst[0] + 32) << "\n";
	std::vector<uint8_t> vchDgst;
	std::copy(&dgst[0], &dgst[0] + 32, std::back_inserter(vchDgst));

	std::cout << base58_encode(&vchDgst[0], &vchDgst[0] + 32) << "\n";
	// sign
	std::vector<uint8_t> vchSig = pKey->Sign(vchDgst);
	std::cout << base58_encode(&vchSig[0], &vchSig[0] + vchSig.size()) << "\n";

	if (pKey->Verify(vchDgst, vchSig))
	{
		std::cout << "verified!!!\n";
	} else {
		std::cout << "not verified!!!\n";
	}

	return true;
}

int main()
{
    TEST(test_key);
    return 0;
}
