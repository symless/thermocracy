//
// Created by Interview on 2019-01-19.
//
#pragma once

#include "JsonMessageBase.h"

class UserJson: public JsonMessageBase
{

public:

    /**
     * \brief
     * \param data the data to be loaded
     * \return if the deserialize was successful
     */
    bool deserialize(const std::string& data) override;

    std::string get_role();
    void set_id(int id);
};