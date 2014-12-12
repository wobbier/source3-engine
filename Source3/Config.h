#pragma once
#include <fstream>
#include <json/json.h>
#include <string>

class Config {
private:
	Json::Value Root;
	Json::Reader Reader;
public:
	Config(const char* file);
	~Config();
	std::string GetValue(std::string value);
};

