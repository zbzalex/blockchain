#include <http/Server.hpp>
#include <nlohmann/json.hpp>
#include <iostream>

using json = nlohmann::json;

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
Server::Server(int port)
{
  // json jsonArray = json::object();
  // jsonArray["version"] = "1.0.0";
  // std::cout << jsonArray.dump() << "\n";
};

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
Server::~Server()
{
  
};