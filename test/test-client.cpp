#include <iostream>
#include <string>
#include <sstream>
#include "Block.h"
#include "BigNum.h"

int main()
{
	Block block;
	std::vector<uint8_t> hash = block.GetHash();

	BigNum hash_ ( &hash[0], hash.size() );

	std::cout << hash_.ToHexString() << "\n";


	return 0;
}
