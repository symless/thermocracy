#include "Server.h"

Server::Server()
{
	m_requestMap["/echo"] = [this](int id, std::string params)->std::string { return m_ThermocracyServer.echo(params); };
	m_requestMap["/user"] = [this](int id,std::string params)->std::string{ return m_ThermocracyServer.user(params);};
}


Server::~Server()
{
}

std::string Server::handle(std::string path, std::string method, int id, std::string payload) {
    return "DUMMY";
}

Server& Server::getInstance()
{
    static Server serverInstance;
    return serverInstance;
}

std::string Server::requestNotFound(int id,std::string params){
    return "DUMMY: request not recognized";
}

Server::requestCallback_t Server::getCallback(std::string name)
{
    auto it = m_requestMap.find(name);
    if ( it == m_requestMap.end() )
        return requestNotFound;

    return it->second;
}
