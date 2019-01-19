#include "Thermocracy.h"
#include "Server.h"
#include "CurrentTemperature.h"
#include "JsonUserVote.h"

#include "EchoJson.h"
#include "UserJson.h"
#include "JsonVoteSummery.h"

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

std::string Thermocracy::user(const std::string& data)
{
	UserJson json;
	if( !json.deserialize(data) )
		return Server::ERROR_400;

	Role_t role = json.get_role();
	ClientID_t id = createNewClient(role);
	json.set_id(id);

	return json.serialize();
}



Thermocracy::ClientID_t Thermocracy::createNewClient(Role_t role){
	// data in map is sorted
	auto nextID = m_clientData.empty()? 1: m_clientData.rbegin()->first + client_ID_incr;
	m_clientData[nextID] = Thermocracy::ClientData_t { true, role, 0, 0 };
	return nextID;
};

void Thermocracy::removeClient(ClientID_t id){
	// data in map is sorted
	m_clientData.erase(id);
};

Thermocracy::ClientData_t& Thermocracy::accessClientData(Thermocracy::ClientID_t id) {
	auto it = m_clientData.find(id);
	if( it == m_clientData.end() ) throw std::runtime_error("No client found");
	return it->second;
}
bool Thermocracy::isClientExistent(Thermocracy::ClientID_t id)
{
	return m_clientData.find(id) != m_clientData.end();
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
	if (vote.deserialize(data) && isClientExistent(id))
	{
		const int voteValue = vote.getUserVote();
		auto &clientData = accessClientData(id);

		std::get<eVote>(clientData) = voteValue;

		rv = "{\"You_Voted\": " + std::to_string(std::get<eVote>(clientData)) +"}";
	}
	return rv;
}

std::string Thermocracy::getVoteSummery()
{
	JsonVoteSummery voteSummery;

	for (std::pair<const int, std::tuple<bool, std::basic_string<char>, int, int>>& client_data : m_clientData)
	{
		voteSummery.addVoteToSummery(std::get<eVote>(client_data.second));
	}
	return voteSummery.serialize();
}
