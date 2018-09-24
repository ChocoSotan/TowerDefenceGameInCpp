#pragma once

#include "Loader.h"

#include <vector>
#include <string>
#include "Turret.h"

class TurretLoader : public Loader {
public:
	TurretLoader() {}
	~TurretLoader() {}

	bool load(const std::string &filename, std::vector<BasicTurret> *vbasicturret, std::vector<MortarTurret> *vmortarturret, std::vector<BlastTurret> *vblastturret);
	void debug();
};

