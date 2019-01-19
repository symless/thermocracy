#pragma once
#include "JsonMessageBase.h"


class CurrentTemperature : public JsonMessageBase
{
public:
	bool deserialize(const std::string& data) override;

	int getTemp();

	void setTemp(int temp);

};