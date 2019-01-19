#pragma once

#include <string>
#include <unordered_map>
#include <functional>
#include <string>

#include "Thermocracy.h"

class Server
{
public:
    using requestCallback_t = std::function<std::string(int, std::string)>;
public:
    static Server& getInstance();
public:
	Server();
	~Server();

	std::string handle(std::string path, std::string method, int id, std::string payload);
	requestCallback_t getCallback(std::string name);
    requestCallback_t operator [](std::string name){ return getCallback(name);};
public:
    static const int NULL_ID = 0;

private:
    static std::string requestNotFound(int id,std::string params);
private:
    std::unordered_map < std::string, requestCallback_t> m_requestMap;
	Thermocracy m_ThermocracyServer;
};

