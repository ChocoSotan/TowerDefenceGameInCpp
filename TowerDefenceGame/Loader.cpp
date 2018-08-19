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
	std::ifstream ifs(filename);
	std::string line;
	std::vector<std::string> buffer;

	const std::vector<std::string> TurretType {
		"Basic",
		"Splash",
		"AoE",
	};

	while (std::getline(ifs, line)) {
		if (line[0] == '#')continue;
		splitString(line, buffer);
		
		for (int i = 0; i < (signed)TurretType.size(); i++) {
			if (TurretType[i].compare(buffer[0]) != 0)continue;
			switch (i) {
			case 0:
				vec.push_back(new BasicTurret(buffer[1],stod(buffer[2]),stod(buffer[3]),stod(buffer[4]),stoi(buffer[5]),stoi(buffer[6]),Vector2D(0,0)));
				break;
			case 1:
				vec.push_back(new MortarTurret(buffer[1], stod(buffer[2]), stod(buffer[3]), stod(buffer[4]), stoi(buffer[5]), stoi(buffer[6]), stod(buffer[7]),stod(buffer[8]),stod(buffer[9]),Vector2D(0, 0)));
				break;
			case 2:
				vec.push_back(new BlastTurret(buffer[1], stod(buffer[2]), stod(buffer[3]), stod(buffer[4]), stoi(buffer[5]), stoi(buffer[6]), Vector2D(0, 0)));
				break;
			}
		}
		

		buffer.clear();
	}
}

