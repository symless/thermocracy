#include "Server.h"

const std::string Server::ERROR_404 = "ERROR_404";
const std::string Server::ERROR_400 = "ERROR_400";
const std::string Server::ERROR_401 = "ERROR_401";

Server::Server()
{

	m_requestMap["/echo"]					= [this](int id, std::string params)->std::string { return m_ThermocracyServer.echo(params); };
	m_requestMap["/temperature/current"]	= [this](int id, std::string params)->std::string { return m_ThermocracyServer.getCurrentTemp(params); };
	m_requestMap["/user"]					= [this](int id,std::string params)->std::string{ return m_ThermocracyServer.user(params);};
	m_requestMap["/votes/vote"]				= [this](int id, std::string params)->std::string { return m_ThermocracyServer.submitUserVote(id, params); };
	m_requestMap["/votes/summary"]				= [this](int id, std::string params)->std::string { return m_ThermocracyServer.getVoteSummery(); };
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
    return Server::ERROR_404;
}

Server::requestCallback_t Server::getCallback(std::string name)
{
    auto it = m_requestMap.find(name);
    if ( it == m_requestMap.end() )
        return requestNotFound;

    return it->second;
}
