#include "ServerSocket.h"
#include "Socket.h"
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <random>
#include <climits>

ServerSocket::ServerSocket(int port, uint32_t max_clients_connected)
{
    //
    // create server socket
    //
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
        throw std::runtime_error("socket() error");

    int optval = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval));

    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(port);

    memset(sin.sin_zero, '\0', sizeof(sin.sin_zero));

    max_clients_connected_ = max_clients_connected;
    connected_ = false;
}

void ServerSocket::remove(Socket *socket)
{
    std::lock_guard<std::mutex> lock(mtx);
    auto found = std::find(clients_.begin(), clients_.end(), socket);
    if (found != clients_.end())
    {
        clients_.erase(found);
    }
}

void ServerSocket::broadcast(Socket *socket, std::vector<uint8_t> &vchBuf)
{
    std::lock_guard<std::mutex> lock(mtx);
    for (
        auto it = clients_.begin();
        it != clients_.end();
        it++)
    {
        if (*it == socket)
            continue;

        (*it)->send(vchBuf);
    }
}

void ServerSocket::start()
{
    if (connected_)
        return;

    //
    // bind port
    //
    if (bind(server_fd, (struct sockaddr *)&sin, sizeof(sin)) < 0)
        throw std::runtime_error("bind() error");

    //
    // listening port
    //
    if (listen(server_fd, 10) < 0)
        throw std::runtime_error("listen() error");

    connected_ = true;

    int new_socket, pid;
    int sinlen = sizeof(sin);

    while (1)
    {
        {
            std::lock_guard<std::mutex> lock(mtx);
            if (clients_.size() >= max_clients_connected_) {
                std::cout << "max clients connected limit!!!\n";
                continue;
            }
        }

        std::cout << "current clients count = "
            << clients_.size()
            << "\n";

        //
        // accept socket
        //
        if ((new_socket = accept(server_fd, (struct sockaddr *)&sin, (socklen_t *)&sinlen)) < 0)
            throw std::runtime_error("accept() error");

        uint32_t id;
        while(1) {
            id = socketCreateId();
            auto found = std::find_if(clients_.begin(), clients_.end(), [&id](Socket *it) -> bool {
                return it->id() == id;
            });
            if (found == clients_.end()) {
                break;
            }
        }

        std::cout << "new socket id: " << id << "\n";

        Socket *socket = new Socket(id, new_socket, (ServerSocket *)this);

        {
            std::lock_guard<std::mutex> lock(mtx);

            clients_.push_back(socket);
        } // mtx autimatically released when lock goes out of scope
        
        std::thread th(std::bind(&ServerSocket::handleClient, this, std::placeholders::_1), socket);

        std::cout << "detach thread\n";

        th.detach();
    }

    //
    // close socket server
    //
    close(server_fd);
}

void ServerSocket::kill()
{
    if (connected_)
    {
        close(server_fd);
    }
}

void ServerSocket::handleClient(Socket *socket)
{
    std::cout << "connected\n";
}

uint32_t ServerSocket::socketCreateId() const noexcept
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, INT_MAX);

    return (uint32_t) dist(gen);
}