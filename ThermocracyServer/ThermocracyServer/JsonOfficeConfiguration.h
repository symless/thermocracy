#pragma once
#include <vector>
#include "JsonMessageBase.h"
class JsonOfficeConfiguration: public JsonMessageBase
{
public:
	bool deserialize(const std::string& data) override;
	int getSeasonDefault(const std::string season);
	std::vector<int> getChangeHours();
};

