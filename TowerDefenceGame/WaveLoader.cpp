#include "WaveLoader.h"

#include "Wave.h"
#include "Enemy.h"

#include <string>
#include <vector>
#include <fstream>

bool WaveLoader::load(std::string filename, std::vector<Wave*> &vec, const Vector2D &pos) {
	using namespace std;

	ifstream ifs(filename);
	string line;
	vector<string> buffer;
	vector<EnemyBase*> venemy;

	const vector<string> EnemyType{
		"Normal",
		"Fast",
		"Armored",
	};

	if (ifs.fail())return false;

	while (getline(ifs, line)) {
		if (line[0] == '#')continue;
		splitString(line, buffer);

		for (int i = 0; i < (signed)EnemyType.size(); i++) {
			if (EnemyType[i].compare(buffer[0]) != 0)continue;
			switch (i) {
			case 0:
				for (int j = 0; j < stoi(buffer[1]); j++) {
					venemy.push_back(new NormalEnemy(stoi(buffer[2]), stod(buffer[3]), stol(buffer[4]), stoll(buffer[5]), pos));
				}
				break;

			case 1:
				// Fast(experimental)
				for (int j = 0; j < stoi(buffer[1]); j++) {
					venemy.push_back(new NormalEnemy(stoi(buffer[2]), stod(buffer[3]), stol(buffer[4]), stoll(buffer[5]), pos));
				}
				break;
			case 2:
				// Armored
				for (int j = 0; j < stoi(buffer[1]); j++) {
					venemy.push_back(new NormalEnemy(stoi(buffer[2]), stod(buffer[3]), stol(buffer[4]), stoll(buffer[5]), pos));
				}
				break;
			}
			vec.push_back(new Wave(venemy));
			break;
		}
		venemy.clear();
		buffer.clear();
	}
	return true;
}