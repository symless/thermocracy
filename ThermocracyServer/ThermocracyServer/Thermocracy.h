#pragma once

#include "EchoJson.h"

class Thermocracy
{
	int m_currentTemperature = 0;


public:

	std::string echo(const std::string& data);

	std::string getCurrentTemp(const std::string& data);

};
