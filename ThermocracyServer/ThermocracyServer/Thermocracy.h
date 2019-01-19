#pragma once

#include "EchoJson.h"

class Thermocracy
{
	float m_currentTemperature = 20.89475693;


public:

	std::string echo(const std::string& data);

	std::string getCurrentTemp(const std::string& data);

};
