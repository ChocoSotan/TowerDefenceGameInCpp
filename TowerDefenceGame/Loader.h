#pragma once

#include <string>
#include <vector>

class Loader {
public:
	Loader() {}
	virtual ~Loader() {}

protected:
	// split string by delimiter and store to container
	void splitString(const std::string &line, std::vector<std::string> &container, const char delim = ',') const;
	
	
};
