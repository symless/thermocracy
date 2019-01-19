#include "Thermocracy.h"
#include "Server.h"
#include "CurrentTemperature.h"

std::string Thermocracy::echo(const std::string & data)
{
	EchoJson echoJson;
	if (echoJson.deserialize(data))
	{
		return echoJson.serialize();
	}
	else
	{
		return Server::ERROR_400;
	}
}

std::string Thermocracy::getCurrentTemp(const std::string& data)
{
	CurrentTemperature curTemp;
	curTemp.deserialize("");
	curTemp.setTemp(m_currentTemperature);
	return curTemp.serialize();
}
