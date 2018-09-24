#include "PathLoader.h"

#include "Vector2D.h"

#include <string>
#include <vector>
#include <fstream>



bool PathLoader::load(const std::string &filename, std::vector<Vector2D> &vpath) {
	using namespace std;
	ifstream ifs(filename);
	string line;
	vector<string> buffer;

	if (ifs.fail())return false;

	while (getline(ifs, line)) {
		if (line[0] == '#')continue;
		splitString(line, buffer);

		vpath.push_back(Vector2D(stoi(buffer[0]), stoi(buffer[1])));

		buffer.clear();
	}



	return true;
}