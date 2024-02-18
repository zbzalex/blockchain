#include <iostream>
#include <openssl/bn.h>

int main()
{
    BIGNUM *p = BN_new();
	BN_rand(p, 512, -1, 0); // 64 bytes

	BIGNUM *g = BN_new();
	BN_rand(g, 16, -1, 0); // 2  bytes

	BIGNUM *privateKeyA = BN_new();
	BIGNUM *privateKeyB = BN_new();
	BIGNUM *publicKeyA = BN_new();
	BIGNUM *publicKeyB = BN_new();
	BIGNUM *secretKeyA = BN_new();
	BIGNUM *secretKeyB = BN_new();

	// BN_hex2bn(&p, p_str); // Задаем значение простого числа p
	// BN_hex2bn(&g, g_str); // Задаем значение генератора g

	// Генерация секретных ключей для Alice и Bob
	BN_rand(privateKeyA, BN_num_bits(p), -1, 0);
	BN_rand(privateKeyB, BN_num_bits(p), -1, 0);

	// Вычисление открытых ключей
	BN_mod_exp(publicKeyA, g, privateKeyA, p, BN_CTX_new()); // Открытый ключ Alice
	BN_mod_exp(publicKeyB, g, privateKeyB, p, BN_CTX_new()); // Открытый ключ Bob

	// Обмен открытыми ключами (в реальности это делается через сервер Телеграма)

	// Вычисление общего секретного ключа
	BN_mod_exp(secretKeyA, publicKeyB, privateKeyA, p, BN_CTX_new());
	BN_mod_exp(secretKeyB, publicKeyA, privateKeyB, p, BN_CTX_new());

	// Проверка, что общие ключи совпадают
	if (BN_cmp(secretKeyA, secretKeyB) == 0)
	{
		char *sharedSecretKeyHex = BN_bn2hex(secretKeyA);
		std::cout << "Shared secret key is: " << sharedSecretKeyHex << std::endl;
		OPENSSL_free(sharedSecretKeyHex);
	}
	else
	{
		std::cout << "Error in key exchange. Shared secret keys do not match." << std::endl;
	}

	// Освобождение памяти
	BN_clear_free(p);
	BN_clear_free(g);
	BN_clear_free(privateKeyA);
	BN_clear_free(privateKeyB);
	BN_clear_free(publicKeyA);
	BN_clear_free(publicKeyB);
	BN_clear_free(secretKeyA);
	BN_clear_free(secretKeyB);
    
    return 0;
}
