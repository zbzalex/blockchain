#ifndef server_socket_h
#define server_socket_h

#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdexcept>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <functional>
#include <thread>
#include <mutex>

class ServerSocket;

#include "Socket.h"

//
//
//
class ServerSocket
{
private:
    // 
    //
    //
    int server_fd;

    //
    //
    //
    struct sockaddr_in sin;

    //
    //
    //
    std::vector<Socket *> clients_;

    //
    //
    //
    std::mutex mtx;

    //
    //
    //
    uint32_t max_clients_connected_;

    //
    //
    //
    bool connected_;

public:
    //
    //
    //
    ServerSocket(int port, uint32_t max_clients_connected);
    
    //
    // remove socket client
    //
    void remove(Socket *socket);
    
    
    void broadcast(Socket * socket, std::vector<uint8_t> &vchBuf);

    //
    // dtor
    //
    ~ServerSocket()
    {
        kill();
    }
    
    //
    // start the server
    //
    void start();

    //
    //
    //
    virtual void handleClient(Socket * socket);

    //
    // close descriptor if connected
    //
    void kill();
private:
    //
    //
    //
    uint32_t socketCreateId() const noexcept;
};

#endif // server_socket_h