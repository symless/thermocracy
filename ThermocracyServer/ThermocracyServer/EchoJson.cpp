#include "EchoJson.h"
#include <sstream>


bool EchoJson::deserialize(const std::string& data)
{

	bool rv = false; //Return value;
	Json::Reader reader;

	if (!reader.parse(data, m_rootNode))
	{
		std::cerr << "failed the read the JSON data: " << data;
		rv = false;
	}
	else
	{
		m_rootNode["newValue"] = true;
		rv = true;
	}

	return rv;
}
