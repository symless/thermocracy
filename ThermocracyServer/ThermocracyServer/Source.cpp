#include <iostream>

#include "3party/json/json.h"

int main(int argc, char* argv[])
{

	const std::string json(R"({ "people": [{"id": 1, "name":"MIKE","surname":"TAYLOR"}, {"id": 2, "name":"TOM","surname":"JERRY"} ]})");


	std::cout << "Hello world!!" << std::endl;

	Json::Value root;
	Json::Reader jsonReader;

	if(!jsonReader.parse(json, root))
	{
		std::cout << "Error reading string" << std::endl;
	}
	const Json::Value mynames = root["people"];
	for (int index = 0; index < mynames.size(); ++index)
	{
		std::cout << mynames[index] << std::endl;
	}
	system("PAUSE");
}
