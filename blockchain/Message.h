#ifndef MESSAGE_H
#define MESSAGE_H

#include <vector>
#include <inttypes.h>

/**
 *
 */
class Message
{
	private:
		std::vector<uint8_t> from_;
		std::vector<uint8_t> pubKey_;
		std::vector<uint8_t> to_;
		std::vector<uint8_t> value_;
		std::vector<uint8_t> signature_;
	public:
		Message();
};

#endif

