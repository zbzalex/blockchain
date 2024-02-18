#ifndef BYTEBUFFER_H
#define BYTEBUFFER_H

#include <inttypes.h>
#include <string>
#include <vector>

class ByteBuffer : public std::vector<uint8_t>
{
private:
    uint32_t position_ = 0;
    uint32_t cap_ = 0;

public:
    ByteBuffer();
    ByteBuffer(std::vector<uint8_t> & v);
    ByteBuffer(uint8_t *pbegin, uint8_t *pend);
    ~ByteBuffer();
    uint32_t Position();
    void SetPosition(uint32_t newPosition);
    uint32_t Cap();
    void Resize(uint32_t newCap);
    void Rewind();
    void Skip(uint32_t val);
    uint32_t Remaining();
    bool HasRemaining();
    int WriteInt32(int32_t val);
    int WriteInt64(int64_t val);
    int WriteBytes(uint8_t *val);
    int WriteBytes(uint8_t *val, uint32_t size);
    int WriteBool(bool val);
    int WriteByte(uint8_t val);
    int WriteDouble(double val);
    int32_t ReadInt32();
    int64_t ReadInt64();
    std::vector<uint8_t> ReadBytes(uint32_t size);
    bool ReadBool();
    uint8_t ReadByte();
    double ReadDouble();
    short ReadShort();
};

#endif // BYTEBUFFER_H
