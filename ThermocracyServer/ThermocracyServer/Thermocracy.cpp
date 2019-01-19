#include "Thermocracy.h"

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
