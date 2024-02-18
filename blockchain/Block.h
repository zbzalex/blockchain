#ifndef BLOCK_H
#define BLOCK_H

#include <inttypes.h>
#include <vector>
#include "Message.h"
#include <string>
#include <sstream>
#include <openssl/sha.h>

/**
 * Block class
 */
class Block
{
	private:
		std::vector<uint8_t> index_;
		std::vector<uint8_t> prevBlockHash_;
		std::vector<uint8_t> hash_;
		std::vector<Message *> messages_;
	public:
		Block()
		{

		}

		std::vector<uint8_t> GetHash()
		{
			std::vector<uint8_t> vch;
			vch.insert(vch.end(), index_.begin(), index_.end());
			vch.insert(vch.end(), prevBlockHash_.begin(), prevBlockHash_.end());
			vch.push_back(messages_.size());
			//vch.insert(vch.end(), messages_.begin(), messages_.end());
			for ( auto msg : messages_ ) {
				//
			}
			
        		uint8_t hash[SHA256_DIGEST_LENGTH];
        		SHA256(&vch[0], vch.size(), &hash[0]);
			
			std::vector<uint8_t> vchOut { SHA256_DIGEST_LENGTH, '\0' };
			std::copy(&hash[0], &hash[0] + SHA256_DIGEST_LENGTH, std::back_inserter(vchOut));
			
			return vchOut;
		}

		
};

#endif

