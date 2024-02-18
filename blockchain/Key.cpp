#include "Key.h"

bool Key::SetPublicKey(const std::vector<uint8_t> &vch)
{
	const uint8_t *pbeg = &vch[0];
	return o2i_ECPublicKey(&pkey, &pbeg, vch.size());
}

