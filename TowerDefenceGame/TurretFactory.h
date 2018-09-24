#pragma once

#include "Turret.h"

#include "TurretLoader.h"

#include "TargetPriority.h"


class TurretFactory {
public:
	TurretFactory() {}
	~TurretFactory() {}

	TurretBase* create(const std::string name, const std::vector<Vector2D> &vpath);
	bool load(const std::string &filename, const std::vector<Vector2D> &vpath);
	const TurretBase* getDataByName(const std::string name) const;
	const std::vector<const TurretBase*> getDataAll() const;

private:
	TurretLoader tl;

	std::vector<BasicTurret> vbasicturret;
	std::vector<MortarTurret> vmortarturret;
	std::vector<BlastTurret> vblastturret;
};

