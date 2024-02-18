#include <iostream>
#include "test.h"
#include <functional>
#include <vector>
#include <memory>
#include <sstream>
#include "ServerSocket.h"
#include "Socket.h"
#include <boost/json.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

class HttpServer : public ServerSocket
{
public:
    HttpServer(int port, uint32_t max_clients_connected) : ServerSocket(port, max_clients_connected)
    {
        std::cout << "ctor called\n";
    }

    void handleClient(Socket *socket) override
    {
        std::vector<uint8_t> vchBuf = socket->recv();

        std::string data{vchBuf.begin(), vchBuf.end()};

        // boost::property_tree::ptree pt;
        // std::istringstream iss(body);
        // boost::property_tree::json_parser::read_json(iss, pt);
        // std::string name = pt.get<std::string>("name");

        //
        // write response
        //
        std::stringstream response_stream;

        // http status
        response_stream << "HTTP/1.1 200 OK\r\n";
        // headers
        response_stream << "Content-Type: application/json\r\n\r\n";

        boost::property_tree::ptree pt;
        pt.put("version", "1.0.0");

        std::ostringstream oss;
        boost::property_tree::json_parser::write_json(oss, pt);

        response_stream << oss.str();
        std::string response = response_stream.str();
        std::vector<uint8_t> vchResponse{response.begin(), response.end()};

        std::cout << "send response..\n";

        socket->send(vchResponse);

        std::cout << "disconnecting..\n";

        // kill socket
        socket->kill();
        
        // erase socket from pool
        socket->serverSocket()->remove(socket);

        std::cout << "disconnected!\n";
        std::cout << "kill thread!!\n";

        // kill thread before out of scope
    }
};

int main()
{
    HttpServer httpServer {8080, 100};
    httpServer.start();

    // std::shared_ptr<HttpServer *> http_server_ =
    //     std::make_shared<HttpServer *>(new HttpServer(8080, 100));
    // (*http_server_)->start();

    return 0;
}
