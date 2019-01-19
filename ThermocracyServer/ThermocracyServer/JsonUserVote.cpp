#include "JsonUserVote.h"


int JsonUserVote::getUserVote()
{
	int rv = INT_MAX;
	if (!m_rootNode.empty())
	{
		rv = m_rootNode["vote"]["change_request"].asInt();
	}
	return rv;
}
