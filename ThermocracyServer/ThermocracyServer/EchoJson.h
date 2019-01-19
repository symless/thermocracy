#pragma once


#include "JsonMessageBase.h"

class EchoJson: public JsonMessageBase
{
	
public:

	/**
	 * \brief
	 * \param data the data to be loaded
	 * \return if the deserialize was successful
	 */
	bool deserialize(const std::string& data) override;
	
};