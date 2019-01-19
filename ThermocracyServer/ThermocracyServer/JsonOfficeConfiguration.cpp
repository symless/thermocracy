#include "JsonOfficeConfiguration.h"

bool JsonOfficeConfiguration::deserialize(const std::string& data) {
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


int JsonOfficeConfiguration::getSeasonDefault(const std::string season) {
	return m_rootNode["office_configuration"]["seasonal_defaults"][season].asInt();
}

std::vector<int> JsonOfficeConfiguration::getChangeHours() {
	std::vector<int> hours;
	auto hoursNode = m_rootNode["office_configuration"]["change_hours"];
	for (auto e = hoursNode.begin(); e != hoursNode.end(); e++) {
		auto ref = *e;
		auto result = ref.asInt();
		hours.push_back(result);
	}

	return hours;
}