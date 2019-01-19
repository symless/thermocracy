#include "Thermocracy.h"
#include "Server.h"
#include "CurrentTemperature.h"
#include "JsonOfficeConfiguration.h"

#include "EchoJson.h"
#include "UserJson.h"

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

std::string Thermocracy::setOfficeConfiguration(int userId, const std::string& data)
{
	JsonOfficeConfiguration json;

	if (!json.deserialize(data))
		return Server::ERROR_400;

	ClientData_t &client = accessClientData(userId);
	Role_t role = std::get<1>(client);
	if (role.compare("admin") != 0) {
		return Server::ERROR_401;
	}

	SeasonDefaults_t defaults = SeasonDefaults_t{ json.getSeasonDefault("summer"), json.getSeasonDefault("autumn"), json.getSeasonDefault("winter"), json.getSeasonDefault("spring") };
	std::vector<ChangeHour_t> hours = json.getChangeHours();

	m_officeConfiguration = SettingData_t{ defaults, hours };

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

std::string Thermocracy::getCurrentTemp(const std::string& data)
{
	CurrentTemperature curTemp;
	curTemp.deserialize("");
	curTemp.setTemp(m_currentTemperature);
	return curTemp.serialize();
}
