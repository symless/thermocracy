#pragma once

#include <string>
#include <unordered_map>
#include <functional>
#include <string>

class Server
{
	std::unordered_map < std::string, std::function<std::string(*)(int, std::string)>> m_requestMap;
public:
	const int NULL_ID = 0;
	Server();
	~Server();

	std::string handle(std::string path, std::string method, int id, std::string payload);
};

