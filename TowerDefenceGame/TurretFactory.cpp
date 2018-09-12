#include "TurretFactory.h"

#include "Turret.h"
#include "TargetPriority.h"
#include "Vector2D.h"

#include <vector>
#include <string>

TurretBase* TurretFactory::create(const std::string name, const std::vector<Vector2D> &vpath) {
	const std::vector<std::string> type = {
		"Normal",
		"Splash",
		"AoE",
	};

	for (int i = 0; i < (signed)vbasicturret.size() - 1; i++) {
		if (vbasicturret[i].getName().compare(name) == 0) {
			BasicTurret *ret = new BasicTurret(vbasicturret[i]);
			ret->changePriority(new ClosestBase(vpath));
			return ret;
		}
	}
	for (int i = 0; i < (signed)vmortarturret.size() - 1; i++) {
		if (vmortarturret[i].getName().compare(name) == 0) {
			MortarTurret *ret = new MortarTurret(vmortarturret[i]);
			ret->changePriority(new ClosestBase(vpath));
			return ret;
		}
	}
	for (int i = 0; i < (signed)vblastturret.size() - 1; i++) {
		if (vblastturret[i].getName().compare(name) == 0) {
			BlastTurret *ret = new BlastTurret(vblastturret[i]);
			ret->changePriority(new ClosestBase(vpath));
			return ret;
		}
	}

	return nullptr;
}

bool TurretFactory::load(const std::string filename, const std::vector<Vector2D> &vpath) {
	if (!tl.load(filename, &this->vbasicturret, &this->vmortarturret, &this->vblastturret))return false;
	for (auto i = vbasicturret.begin(); i != vbasicturret.end(); ++i) {
		i->changePriority(new ClosestBase(vpath));
	}
	for (auto i = vmortarturret.begin(); i != vmortarturret.end(); ++i) {
		i->changePriority(new ClosestBase(vpath));
	}
	for (auto i = vblastturret.begin(); i != vblastturret.end(); ++i) {
		i->changePriority(new ClosestBase(vpath));
	}

	return true;
}

const TurretBase* TurretFactory::getDataByName(const std::string name) const {
	for (int i = 0; i < (signed)vbasicturret.size() - 1; i++) {
		if (vbasicturret[i].getName().compare(name) == 0) {
			return &vbasicturret[i];
		}
	}
	for (int i = 0; i < (signed)vmortarturret.size() - 1; i++) {
		if (vmortarturret[i].getName().compare(name) == 0) {
			return &vmortarturret[i];
		}
	}
	for (int i = 0; i < (signed)vblastturret.size() - 1; i++) {
		if (vblastturret[i].getName().compare(name) == 0) {
			return &vblastturret[i];
		}
	}
	return nullptr;
}

const std::vector<const TurretBase*> TurretFactory::getDataAll() const {
	std::vector<const TurretBase*> ret;
	for (int i = 0; i < (signed)vbasicturret.size(); i++) {
		ret.push_back((TurretBase*)&vbasicturret[i]);
	}
	for (int i = 0; i < (signed)vmortarturret.size(); i++) {
		ret.push_back((TurretBase*)&vmortarturret[i]);
	}
	for (int i = 0; i < (signed)vblastturret.size(); i++) {
		ret.push_back((TurretBase*)&vblastturret[i]);
	}
	return ret;
}