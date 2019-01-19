#include "sstream"

#include "JsonMessageBase.h"

std::string JsonMessageBase::serialize()
{
	
	std::string rv;
	if (!m_rootNode.empty())
	{
		std::stringstream stream;

		stream << m_rootNode << std::endl;

		rv = stream.str();
	}

	return rv;

}
