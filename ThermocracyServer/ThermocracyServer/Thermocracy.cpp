#include "Thermocracy.h"
#include "Server.h"
#include "CurrentTemperature.h"
#include "JsonUserVote.h"

std::string Thermocracy::echo(const std::string & data) const
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

std::string Thermocracy::getCurrentTemp(const std::string& data) const
{
	CurrentTemperature curTemp;
	curTemp.deserialize("");
	curTemp.setTemp(m_currentTemperature);
	return curTemp.serialize();
}

std::string Thermocracy::submitUserVote(const int id, const std::string& data)
{
	std::string rv = Server::ERROR_400;
	JsonUserVote vote;
	if (vote.deserialize(data))
	{
		int voteValue = vote.getUserVote();
		//TODO Actually do something with the data
		rv = "{\"You_Voted\": true}";
	}
	return rv;
}
