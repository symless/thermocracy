#include "CurrentTemperature.h"

bool CurrentTemperature::deserialize(const std::string& data)
{
	bool rv = false;
	if (data.empty())
	{
		rv = JsonMessageBase::deserialize("{}");
	}
	else
	{
		rv = JsonMessageBase::deserialize(data);
	}
	return rv;
}

int CurrentTemperature::getTemp()
{
	int temp = INT_MAX;
	if (!m_rootNode.empty())
	{
		temp = m_rootNode["current_temperature"].asInt();
	}
	return temp;
}

void CurrentTemperature::setTemp(int temp)
{
	m_rootNode["current_temperature"] = temp;
}
