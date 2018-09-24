#include "FieldLoader.h"

#include "Terrain.h"
#include "Vector2D.h"

#include <string>
#include <vector>
#include <fstream>


bool FieldLoader::load(const std::string &filename, std::vector<std::vector<TerrainBase*>> &vec, const Vector2D &pos, const int size) {
	using namespace std;
	ifstream ifs(filename);
	string line;
	vector<string> buffer;
	int column = 0;
	int row = 0;
	vector<TerrainBase*> tmp;

	if (ifs.fail())return false;

	// can place turret
	while (getline(ifs, line)) {
		if (line[0] == '#')continue;
		splitString(line, buffer);

		for (column = 0; column < (signed)buffer.size(); column++) {
			if (stoi(buffer[column]) == 0) {
				tmp.push_back(new BasicTerrain(false, Vector2D(pos.getX() + row * size, pos.getY() + column * size)));
			}
			else {
				tmp.push_back(new BasicTerrain(true, Vector2D(pos.getX() + row * size, pos.getY() + column * size)));
			}
		}

		vec.push_back(tmp);
		tmp.clear();
		row++;
		buffer.clear();
	}
	ifs.clear();


	return true;
}

bool FieldLoader::initField(std::string filename_texture, std::string filename_id, std::vector<std::vector<TerrainBase*>> &vec, Texture *texture) {
	using namespace std;
	ifstream ifs(filename_id);
	string line;
	vector<string> buffer;
	map<int, string> dictionary;
	int row = 0;

	while (getline(ifs, line)) {
		if (line[0] == '#')continue;
		splitString(line, buffer);

		dictionary.insert(std::make_pair(stoi(buffer[0]), buffer[1]));

		row++;
		buffer.clear();
	}

	ifs.close();
	ifs.open(filename_texture);
	if (ifs.fail())return false;
	row = 0;

	while (getline(ifs, line)) {
		if (line[0] == '#')continue;
		splitString(line, buffer);

		for (int i = 0; i < (signed)buffer.size(); i++) {
			if (dictionary.find(stoi(buffer[i])) != dictionary.end()) {
				vec[i][row]->init(texture, dictionary[stoi(buffer[i])]);
			}
			else return false;
		}

		row++;
		buffer.clear();
	}


	return true;
}