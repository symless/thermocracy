#pragma once
#include "JsonMessageBase.h"

class JsonVoteSummery : public JsonMessageBase
{
public:

	JsonVoteSummery();

	void addVoteToSummery(const int vote);
};