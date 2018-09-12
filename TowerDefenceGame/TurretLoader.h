#pragma once

#include "Loader.h"

class TurretLoader : public Loader {
public:
	TurretLoader() {}
	~TurretLoader() {}

	bool load(std::string filename, std::vector<BasicTurret> *vbasicturret, std::vector<MortarTurret> *vmortarturret, std::vector<BlastTurret> *vblastturret);
	void debug();
};

