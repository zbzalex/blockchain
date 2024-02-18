#include "ServerSocket.h"
#include "Socket.h"

//
//
//
std::string Socket::ip() const
{
        struct sockaddr_in local_sin;
        socklen_t local_sinlen = sizeof(local_sin);

        getsockname(socket_, (struct sockaddr *)&local_sin, &local_sinlen);

        int ip[4];
        ip[0] = (int)( local_sin.sin_addr.s_addr & 0xff );
        ip[1] = (int)((local_sin.sin_addr.s_addr & 0xff00) >> 8);
        ip[2] = (int)((local_sin.sin_addr.s_addr & 0xff0000) >> 16);
        ip[3] = (int)((local_sin.sin_addr.s_addr & 0xff000000) >> 24);

        char ipstr[15]; // 127.127.127.127

        sprintf(ipstr, "%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[2]);

        return ipstr;
}

//
//
//
std::vector<uint8_t> Socket::recv() const
{
        if (!connected_)
        {
                std::vector<uint8_t> vchBuf;

                return vchBuf;
        }

        //
        // read body
        //
        std::stringstream data_stream;

        uint8_t *buf = (uint8_t *)malloc(1024);
        uint32_t buf_size = 0;
        uint64_t len = 0;

        while (1)
        {
                len = read(socket_, buf, 1024);
                data_stream << buf;

                if (len < 1024)
                        break;
        }

        std::string data = data_stream.str();
        std::vector<uint8_t> vchBuf{data.begin(), data.end()};

        return vchBuf;
}

//
//
//
bool Socket::send(const std::vector<uint8_t> &vchBuf) const
{
        if (!connected_)
                return false;

        return write(socket_, vchBuf.data(), vchBuf.size()) == vchBuf.size();
}

//
//
//
void Socket::kill()
{
        if (connected_)
        {
                connected_ = false;
                close(socket_);
        }
}
