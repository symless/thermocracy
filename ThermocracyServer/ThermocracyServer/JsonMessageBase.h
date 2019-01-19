#pragma once
#include "3party/json/json.h"

class JsonMessageBase
{
	
public:

	JsonMessageBase() = default;

	virtual ~JsonMessageBase() = default;

	/**
	 * \brief Serializes the containing data
	 * \return the json formatted data contained within
	 */
	virtual std::string serialize();

	/**
	 * \brief 
	 * \param data the data to be loaded
	 * \return if the deserialize was successful
	 */
	virtual bool deserialize(const std::string& data) = 0;

protected:

	
	/**
	 * \brief The root node of the json data
	 */
	Json::Value m_rootNode;

};