#pragma once

#include "Enemy.h"
#include "Terrain.h"
#include "Turret.h"



#include <string>
#include <sstream>
#include <vector>
#include <fstream>


class Loader {
public:
	Loader() {}
	virtual ~Loader() {}

protected:
	// split string by delimiter and store to container
	void splitString(const std::string &line, std::vector<std::string> &container, const char delim = ',');
	
	
};

// split string by delimiter and store to container
void Loader::splitString(const std::string &line, std::vector<std::string> &container, const char delim) {
	std::istringstream iss(line);
	std::string str;
	
	while (std::getline(iss,str,delim)) {
		container.push_back(str);
	}
}


class FieldLoader : public Loader {
public:
	FieldLoader() {}
	~FieldLoader() {}

	bool load(std::string filename, std::vector<TerrainBase*> &vec);
private:
	// create and store instance of T
	void stock(std::vector<TerrainBase*> &vec);
};

class TurretLoader : public Loader {
public:
	TurretLoader() {}
	~TurretLoader() {}

	bool load(std::string filename, std::vector<TurretBase*> &vec);

private:
	void stock(std::vector<TurretBase> &vturret);
};