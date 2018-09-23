#include "TextureLoader.h"

#include "Texture.h"

#include <string>
#include <vector>
#include <fstream>

bool TextureLoader::load(std::string filename, Texture *texture) {
	using namespace std;

	ifstream ifs(filename);
	string line;
	vector<string> buffer;
	vector<string> vfilename;

	if (ifs.fail())return false;

	while (getline(ifs, line)) {
		if (line[0] == '#')continue;
		//splitString(line, buffer);

		if (!texture->pool(line))return false;

		buffer.clear();
	}



	return true;
}