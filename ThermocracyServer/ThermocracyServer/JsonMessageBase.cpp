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

bool JsonMessageBase::deserialize(const std::string& data)
{
	bool rv = true; //Return value;
	Json::Reader reader;

	if (!reader.parse(data, m_rootNode))
	{
		std::cerr << "failed the read the JSON data: " << data;
		rv = false;
	}
	else
	{
		rv = true;
	}
	return rv;
}

