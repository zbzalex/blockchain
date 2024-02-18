#ifndef socket_h
#define socket_h

#include <stdexcept>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/types.h>
#include <sstream>
#include <functional>
#include <memory>
#include <vector>
#include <algorithm>

class Socket;

#include "ServerSocket.h"

//
//
//
class Socket
{
private:
    //
    //
    //
    uint32_t id_;

    //
    //
    //
    int socket_;

    //
    //
    //
    ServerSocket *server_socket_;

    //
    //
    //
    bool connected_;

public:
    //
    // ctor
    //
    Socket(uint32_t id, int socket, ServerSocket *server_socket)
        : id_(id), socket_(socket), server_socket_(server_socket), connected_(true)
    {
    }

    //
    //
    //
    inline uint32_t id()
    {
        return id_;
    }

    //
    //
    //
    std::string ip() const;

    //
    //
    //
    ServerSocket *serverSocket()
    {
        return server_socket_;
    }

    //
    //
    //
    std::vector<uint8_t> recv() const;

    //
    //
    //
    bool send(const std::vector<uint8_t> &vchBuf) const;

    //
    // indicates is client connected
    //
    bool is_connected() const
    {
        return connected_;
    }

    //
    //
    //
    void kill();
};

#endif // socket_h