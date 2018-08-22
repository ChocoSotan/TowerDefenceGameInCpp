#pragma once

#include "Turret.h"



class TurretFactory {
public:
	TurretFactory() {}
	~TurretFactory() {}

	TurretBase* create(const BasicTurret &turret);
	TurretBase* create(const MortarTurret &turret);
	TurretBase* create(const BlastTurret &turret);

private:

};

TurretBase* TurretFactory::create(const BasicTurret &turret) {
	return new BasicTurret(turret);
}

TurretBase* TurretFactory::create(const MortarTurret &turret) {
	return new MortarTurret(turret);
}

TurretBase* TurretFactory::create(const BlastTurret &turret) {
	return new BlastTurret(turret);
}