#pragma once

#include <map>
#include <string>

class Sound final {
public:
	Sound() {}
	~Sound() {}

	bool play(const std::string &filename) const;
	bool pool(const std::string &filename);

private:
	std::map<std::string, int> sounds;
};