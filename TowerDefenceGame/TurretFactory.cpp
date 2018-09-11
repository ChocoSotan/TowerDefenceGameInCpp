#include"TurretFactory.h"

TurretBase* TurretFactory::create(const TurretBase &turret) {
	if (turret.getName() == "BasicTurret") {
		return createBasicTurret(turret);
	}
	if (turret.getName() == "MortarTurret") {
		return createBasicTurret(turret);
	}
	if (turret.getName() == "BlastTurret") {
		return createBasicTurret(turret);
	}
	return createBasicTurret(turret);
}

BasicTurret* TurretFactory::createBasicTurret(const TurretBase &turret) {
	return new BasicTurret(turret);
}

MortarTurret* TurretFactory::createMortarTurret(const TurretBase &turret) {
	return new MortarTurret(turret);
}

BlastTurret* TurretFactory::createBlastTurret(const TurretBase &turret) {
	return new BlastTurret(turret);
}
