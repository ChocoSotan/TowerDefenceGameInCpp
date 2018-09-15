#include "SoundLoader.h"

#include "Sound.h"

#include <vector>
#include <string>
#include <fstream>

bool SoundLoader::load(const std::string &filename, Sound *sound) {
	using namespace std;
	ifstream ifs(filename);
	string line;
	vector<string> buffer;

	if (ifs.fail())return false;

	while (getline(ifs, line)) {
		if (line[0] == '#')continue;

		if (!sound->pool(line))return false;
	}
	return true;
}