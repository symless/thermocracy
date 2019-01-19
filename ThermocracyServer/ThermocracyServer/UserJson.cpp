//
// Created by Interview on 2019-01-19.
//

#include "UserJson.h"

#include <string>


bool UserJson::deserialize(const std::string& data)
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

std::string UserJson::get_role()
{
    if (!m_rootNode.empty()) throw std::runtime_error("no JSON 'role' filed found");
        return m_rootNode["role"].asString();
}

void UserJson::set_id(int id)
{
    m_rootNode["id"] = std::to_string(id);
}