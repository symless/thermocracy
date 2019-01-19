#include "EchoJson.h"
#include <sstream>


bool EchoJson::deserialize(const std::string& data)
{

	bool rv = false; //Return value;

	if (JsonMessageBase::deserialize(data))
	{
		m_rootNode["newValue"] = true;
		rv = true;
	}

	return rv;
}
