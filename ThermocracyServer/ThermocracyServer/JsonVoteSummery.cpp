#include "JsonVoteSummery.h"

JsonVoteSummery::JsonVoteSummery()
{
	int index = -2;
	m_rootNode["vote_summary"][std::to_string(index++)] = 0;
	m_rootNode["vote_summary"][std::to_string(index++)] = 0;
	m_rootNode["vote_summary"][std::to_string(index++)] = 0;
	m_rootNode["vote_summary"][std::to_string(index++)] = 0;
	m_rootNode["vote_summary"][std::to_string(index)] = 0;
}

void JsonVoteSummery::addVoteToSummery(const int vote)
{
	int currentcount = m_rootNode["vote_summary"][std::to_string(vote)].asInt();

	m_rootNode["vote_summary"][std::to_string(vote)] = currentcount + 1;

}
