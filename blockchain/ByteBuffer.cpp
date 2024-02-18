#include "ByteBuffer.h"
#include <inttypes.h>
#include <memory>
#include <string.h>
#include <iostream>
#include <algorithm>

ByteBuffer::ByteBuffer()
{
	cap_ = -1;
	position_ = 0;
	Rewind();
}

//
//
//
ByteBuffer::ByteBuffer(std::vector<uint8_t> & v) : std::vector<uint8_t>()
{
	assign( v.begin(), v.end() );	
	Rewind();

	cap_ = v.size();
}

//
//
//
ByteBuffer::ByteBuffer(uint8_t *pbegin, uint8_t *pend)
{
	std::vector<uint8_t> v { pbegin, pend };
	assign( v.begin(), v.end() );
	Rewind();

	cap_ = v.size();
}

//
//
//
ByteBuffer::~ByteBuffer()
{
    clear();
}

//
//
//
uint32_t ByteBuffer::Position()
{
    return position_;
}

//
//
//
void ByteBuffer::SetPosition(uint32_t newPosition)
{
    position_ = newPosition;
}

//
//
//
void ByteBuffer::Rewind()
{
    position_ = 0;
}

//
//
//
uint32_t ByteBuffer::Remaining()
{
    return cap_ == -1 ? -1 : position_ > cap_ ? 0
                                              : cap_ - position_;
}

//
//
//
bool ByteBuffer::HasRemaining()
{
    return Remaining() != 0;
}

//
//
//
void ByteBuffer::Skip(uint32_t val)
{
    if (position_ + val < cap_)
    {
        SetPosition(position_ + val);
    }
}

//
//
//
uint32_t ByteBuffer::Cap()
{
    return cap_;
}

void ByteBuffer::Resize(uint32_t newCap)
{
    cap_ = newCap;
    resize(newCap);
}

std::vector<uint8_t> ByteBuffer::ReadBytes(uint32_t size)
{
	std::vector<uint8_t> v ( size, '\0' );
    	if (position_ + size <= cap_)
    	{
		v.insert( v.begin(), (&(* this)[0]) + position_, (&(* this)[0]) + position_ + size );
		position_ += size;
    	}

	return v;
}

uint8_t ByteBuffer::ReadByte()
{
    if (position_ + 1 <= cap_)
    {
	uint32_t oldPosition = position_;
	position_ ++;

        return (* this)[oldPosition];
    }

    return (uint8_t) 0;
}

int32_t ByteBuffer::ReadInt32()
{
    if (position_ + 4 > cap_)
        return 0;

    uint32_t result = ((uint32_t)((*this)[0] & 0xff)) |
                      ((uint32_t)((*this)[1] & 0xff) << 8) |
                      ((uint32_t)((*this)[2] & 0xff) << 16) |
                      ((uint32_t)((*this)[3] & 0xff) << 24);

    position_ += 4;

    return result;
}

int64_t ByteBuffer::ReadInt64()
{
    if (position_ + 8 > cap_)
        return 0;

    uint32_t result = ((uint32_t)((* this)[0] & 0xff)) |
                      ((uint32_t)((* this)[1] & 0xff) << 8) |
                      ((uint32_t)((* this)[2] & 0xff) << 16) |
                      ((uint32_t)((* this)[3] & 0xff) << 24) |
                      ((uint32_t)((* this)[4] & 0xff) << 32) |
                      ((uint32_t)((* this)[5] & 0xff) << 40) |
                      ((uint32_t)((* this)[6] & 0xff) << 48) |
                      ((uint32_t)((* this)[7] & 0xff) << 54)
                      ;

    position_ += 8;

    return result;
}

int ByteBuffer::WriteInt32(int32_t val)
{
    if (cap_ != -1 && position_ + 4 > cap_)
        return 0;

    uint8_t buf[4];

    buf[0] = (uint8_t)(val);
    buf[1] = (uint8_t)(val >> 8);
    buf[2] = (uint8_t)(val >> 16);
    buf[3] = (uint8_t)(val >> 24);

    push_back(buf[0]);
    push_back(buf[1]);
    push_back(buf[2]);
    push_back(buf[3]);

    position_ += 4;

    return 1;
}

int ByteBuffer::WriteInt64(int64_t val)
{
    if (cap_ != -1 && position_ + 8 > cap_)
        return 0;

    uint8_t buf[8];

    buf[0] = (uint8_t)(val);
    buf[1] = (uint8_t)(val >> 8);
    buf[2] = (uint8_t)(val >> 16);
    buf[3] = (uint8_t)(val >> 24);
    buf[4] = (uint8_t)(val >> 32);
    buf[5] = (uint8_t)(val >> 40);
    buf[6] = (uint8_t)(val >> 48);
    buf[7] = (uint8_t)(val >> 54);

    push_back(buf[0]);
    push_back(buf[1]);
    push_back(buf[2]);
    push_back(buf[3]);
    push_back(buf[4]);
    push_back(buf[5]);
    push_back(buf[6]);
    push_back(buf[7]);

    position_ += 8;

    return 1;
}

int ByteBuffer::WriteByte(uint8_t val)
{
    if (cap_ != -1 && position_ + 1 > cap_)
        return 0;

    push_back(val);

    position_++;

    return 1;
}

int ByteBuffer::WriteBytes(uint8_t *val, uint32_t size)
{
    if (cap_ != -1 && position_ + size > cap_)
        return 0;
    
    insert(begin() + position_, val, val + size);
    position_ += size;

    return 1;
}

short ByteBuffer::ReadShort()
{
	std::vector<uint8_t> v = ReadBytes(2);
	return *((short *) &v[0]);
}
