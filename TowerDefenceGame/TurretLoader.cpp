#include "TurretLoader.h"

#include "Turret.h"
#include "Vector2D.h"

#include <vector>
#include <fstream>
#include <sstream>

bool TurretLoader::load(std::string filename, std::vector<BasicTurret> *vbasicturret, std::vector<MortarTurret> *vmortarturret, std::vector<BlastTurret> *vblastturret) {
	using namespace std;
	ifstream ifs(filename);
	string line;
	vector<string> buffer;

	const vector<string> TurretType{
		"Basic",
		"Splash",
		"AoE",
	};

	if (ifs.fail())return false;

	while (getline(ifs, line)) {
		if (line[0] == '#')continue;
		splitString(line, buffer);

		for (int i = 0; i < (signed)TurretType.size(); i++) {
			if (TurretType[i].compare(buffer[0]) != 0)continue;
			switch (i) {
			case 0:
			{
				vbasicturret->push_back(BasicTurret(buffer[1], buffer[0], stod(buffer[2]), stod(buffer[3]), stod(buffer[4]), stoi(buffer[5]), stoi(buffer[6]), Vector2D(0, 0)));
				break;
			}
			case 1:
			{
				vmortarturret->push_back(MortarTurret(buffer[1], buffer[0], stod(buffer[2]), stod(buffer[3]), stod(buffer[4]), stoi(buffer[5]), stoi(buffer[6]), Vector2D(0, 0), stod(buffer[7]), stod(buffer[8]), stod(buffer[9])));
				break;
			}
			case 2:
			{
				vblastturret->push_back(BlastTurret(buffer[1], buffer[0], stod(buffer[2]), stod(buffer[3]), stod(buffer[4]), stoi(buffer[5]), stoi(buffer[6]), Vector2D(0, 0)));
				break;
			}
			}
		}
		buffer.clear();
	}
	return true;
}

void TurretLoader::debug() {
	
}


