#include"TurretFactory.h"

TurretBase* TurretFactory::create(const TurretBase &turret, int channel) {
	switch (channel) {
	case 0:
		return createBasicTurret(turret);
	case 1:
		return createBasicTurret(turret);
	case 2:
		return createBasicTurret(turret);
	case 3:
		return createBasicTurret(turret);
	case 4:
		return createMortarTurret(turret); 
	case 5:
		return createBlastTurret(turret);
	default:
		break;
	}
	return createBasicTurret(turret);
}

TurretBase* TurretFactory::createBasicTurret(const TurretBase &turret) {
	return new BasicTurret(turret);
}

TurretBase* TurretFactory::createMortarTurret(const TurretBase &turret) {
	return new MortarTurret(turret);
}

TurretBase* TurretFactory::createBlastTurret(const TurretBase &turret) {
	return new BlastTurret(turret);
}