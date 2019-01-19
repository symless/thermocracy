#pragma once

#include <map>
#include <tuple>

class Thermocracy
{
public:
	enum
	{
		  eActive
		, eRole
		, eVote
		, eVoteDate
	};

	using Vote_t = int;
	using Active_t = bool;
	using ClientID_t = int;
	using VotingDate_t = int;
	using Role_t = std::string;
	using ClientData_t = std::tuple<Active_t,Role_t,Vote_t,VotingDate_t>;
	static constexpr ClientID_t client_ID_incr = 1;
	float m_currentTemperature = 20.89475693;


public:
	std::string echo(const std::string& data) const;
	std::string user(const std::string& data);

	std::string getCurrentTemp(const std::string& data) const;
	std::string submitUserVote(const int id, const std::string& data);
private:
	ClientID_t createNewClient(Role_t);
	void removeClient(ClientID_t);
	ClientData_t& accessClientData(ClientID_t);
	bool isClientExistent(ClientID_t);
private:
	std::map<ClientID_t,ClientData_t> m_clientData;


};
