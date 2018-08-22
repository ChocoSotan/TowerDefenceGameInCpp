#include "Loader.h"

#include "Terrain.h"
#include "Turret.h"
#include "TurretFactory.h"
#include "WaveSystem.h"
#include "TargetPriority.h"

#include <string>
#include <sstream>
#include <vector>
#include <fstream>


// split string by delimiter and store to container
void Loader::splitString(const std::string &line, std::vector<std::string> &container, const char delim) {
	std::istringstream iss(line);
	std::string str;

	while (std::getline(iss, str, delim)) {
		container.push_back(str);
	}
}

bool FieldLoader::load(std::string filename, std::vector<TerrainBase*> &vec) {
	return true;
}

bool TurretLoader::load(std::string filename, std::vector<TurretBase*> &vec) {
	using namespace std;
	ifstream ifs(filename);
	string line;
	vector<string> buffer;
	TurretBase *turret;

	const vector<string> TurretType {
		"Basic",
		"Splash",
		"AoE",
	};

	while (getline(ifs, line)) {
		if (line[0] == '#')continue;
		splitString(line, buffer);
		
		for (int i = 0; i < (signed)TurretType.size(); i++) {
			if (TurretType[i].compare(buffer[0]) != 0)continue;
			switch (i) {
			case 0:
				turret = new BasicTurret(buffer[1],stod(buffer[2]),stod(buffer[3]),stod(buffer[4]),stoi(buffer[5]),stoi(buffer[6]),Vector2D(0,0));
				break;
			case 1:
				turret = new MortarTurret(buffer[1], stod(buffer[2]), stod(buffer[3]), stod(buffer[4]), stoi(buffer[5]), stoi(buffer[6]), Vector2D(0, 0), stod(buffer[7]), stod(buffer[8]), stod(buffer[9]));
				break;
			case 2:
				turret = new BlastTurret(buffer[1], stod(buffer[2]), stod(buffer[3]), stod(buffer[4]), stoi(buffer[5]), stoi(buffer[6]), Vector2D(0, 0));
				break;
			}
			vec.push_back(turret);
		}
		buffer.clear();
	}
	return true;
}




bool WaveLoader::load(std::string filename, std::vector<Wave*> &vec, Vector2D &pos) {
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

	while (getline(ifs, line)) {
		if (line[0] == '#')continue;
		splitString(line, buffer);

		for (int i = 0; i < (signed)EnemyType.size(); i++) {
			if (EnemyType[i].compare(buffer[0]) != 0)continue;
			switch (i) {
			case 0:
				for (int j = 0; j < stoi(buffer[1]); j++) {
					venemy.push_back(new NormalEnemy(stoi(buffer[2]), stod(buffer[3]), stol(buffer[4]), stoll(buffer[5]),pos));
				}
				break;

			case 1:
				// Fast(experimental)
				for (int j = 0; j < stoi(buffer[1]); j++) {
					venemy.push_back(new NormalEnemy(stoi(buffer[2]), stod(buffer[3]), stol(buffer[4]), stoll(buffer[5]),pos));
				}
				break;
			case 2:
				// Armored
				for (int j = 0; j < stoi(buffer[1]); j++) {
					venemy.push_back(new NormalEnemy(stoi(buffer[2]), stod(buffer[3]), stol(buffer[4]), stoll(buffer[5]),pos));
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

bool PathLoader::load(std::string filename, std::vector<Vector2D>& vpath) {
	using namespace std;
	ifstream ifs(filename);
	string line;
	vector<string> buffer;


	while (getline(ifs, line)) {
		if (line[0] == '#')continue;
		splitString(line, buffer);

		vpath.push_back(Vector2D(stoi(buffer[0]),stoi(buffer[1])));

		buffer.clear();
	}



	return true;
}

