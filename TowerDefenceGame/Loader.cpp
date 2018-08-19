#include "Loader.h"

#include "Terrain.h"
#include "Turret.h"

#include "TurretFactory.h"

#include <string>
#include <sstream>
#include <vector>
#include <fstream>




bool FieldLoader::load(std::string filename, std::vector<TerrainBase*> &vec) {

}

bool TurretLoader::load(std::string filename, std::vector<TurretBase*> &vec) {
	using namespace std;
	ifstream ifs(filename);
	string line;
	vector<string> buffer;

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
				vec.push_back(new BasicTurret(buffer[1],stod(buffer[2]),stod(buffer[3]),stod(buffer[4]),stoi(buffer[5]),stoi(buffer[6]),Vector2D(0,0)));
				break;
			case 1:
				vec.push_back(new MortarTurret(buffer[1], stod(buffer[2]), stod(buffer[3]), stod(buffer[4]), stoi(buffer[5]), stoi(buffer[6]), Vector2D(0, 0), stod(buffer[7]), stod(buffer[8]), stod(buffer[9])));
				break;
			case 2:
				vec.push_back(new BlastTurret(buffer[1], stod(buffer[2]), stod(buffer[3]), stod(buffer[4]), stoi(buffer[5]), stoi(buffer[6]), Vector2D(0, 0)));
				break;
			}
		}
		

		buffer.clear();
	}
}

bool EnemyLoader::load(std::string filename, std::vector<EnemyBase*> &vec) {
	using namespace std;
	
	ifstream ifs(filename);
	string line;
	vector<string> buffer;
	
	const vector<string> EnemyType{
		"Normal",
	};

	while (getline(ifs, line)) {
		if (line[0] == '#')continue;
		splitString(line, buffer);

		for (int i = 0; i < (signed)EnemyType.size(); i++) {
			if (EnemyType[i].compare(buffer[0]) != 0)continue;
			switch (i) {
			case 0:
				vec.push_back(new NormalEnemy(stod(buffer[1]), stod(buffer[2]), stol(buffer[3]),stoll(buffer[4])));
				break;
			}
		}

		buffer.clear();
	}
}

