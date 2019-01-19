#pragma once

#include <map>
#include <vector>
#include <tuple>

class Thermocracy
{
public:
	using Vote_t = int;
	using Active_t = bool;
	using ClientID_t = int;
	using VotingDate_t = int;
	using Role_t = std::string;
	using ClientData_t = std::tuple<Active_t,Role_t,Vote_t,VotingDate_t>;
	using SummerDefault_t = int;
	using AutumnDefault_t = int;
	using WinterDefault_t = int;
	using SpringDefault_t = int;
	using ChangeHour_t = int;
	using SeasonDefaults_t = std::tuple<SummerDefault_t, AutumnDefault_t, WinterDefault_t, SpringDefault_t>;
	using SettingData_t = std::tuple<SeasonDefaults_t, std::vector<ChangeHour_t>>;
	static constexpr ClientID_t client_ID_incr = 1;
	float m_currentTemperature = 20.89475693;


public:
	std::string echo(const std::string& data);
	std::string user(const std::string& data);
	std::string setOfficeConfiguration(int userId, const std::string& data);
	std::string getCurrentTemp(const std::string& data);
private:
	ClientID_t createNewClient(Role_t);
	void removeClient(ClientID_t);
	ClientData_t& accessClientData(ClientID_t);
	bool isClientExistent(ClientID_t);
private:
	std::map<ClientID_t,ClientData_t> m_clientData;
	SettingData_t m_officeConfiguration;


};
