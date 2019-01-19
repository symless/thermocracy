#include "Thermocracy.h"
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
		return "";
	}
}

std::string Thermocracy::getCurrentTemp(const std::string& data)
{
	CurrentTemperature curTemp;
	curTemp.deserialize("");
	curTemp.setTemp(m_currentTemperature);
	return curTemp.serialize();
}
