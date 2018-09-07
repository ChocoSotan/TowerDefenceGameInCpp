#pragma once

#include <map>
#include <string>
#include <vector>

#include "DxLib.h"

class Texture final {
public:
	Texture() {}
	~Texture() {}

	bool pool(const std::string &filename);
	bool pool(const std::vector<std::string> &vfilename);

	bool deleteHandle(const std::string &filename);
	bool deleteHandle(const std::vector<std::string> &vfilename);
	bool deleteHandleAll();

	int getHandle(const std::string &filename) const;
	std::vector<int> getHandle(const std::vector<std::string> &vfilename) const;
	
private:
	std::map<std::string,int> dictionary;
};