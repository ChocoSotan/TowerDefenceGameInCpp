#include "Loader.h"

#include "Terrain.h"
#include "Turret.h"
#include "TurretFactory.h"
#include "WaveSystem.h"
#include "TargetPriority.h"
#include "Button.h"
#include "ToggleButton.h"

#include <string>
#include <vector>
#include <sstream>


// split string by delimiter and store to container
void Loader::splitString(const std::string &line, std::vector<std::string> &container, const char delim) {
	std::istringstream iss(line);
	std::string str;

	while (std::getline(iss, str, delim)) {
		container.push_back(str);
	}
}

