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
	std::ifstream ifs(filename);
	std::string line;
	std::vector<std::string> buffer;
	TurretFactory factory;

	while (std::getline(ifs, line)) {
		splitString(line, buffer);
		
		if (buffer[0] == "Basic") vec.push_back(factory.create(Basic, buffer[1], std::stod(buffer[2]), std::stod(buffer[3]), std::stod(buffer[4])));
		

		buffer.clear();
	}
}


void TurretLoader::stock(std::vector<TurretBase> &vturret) {
	
}

