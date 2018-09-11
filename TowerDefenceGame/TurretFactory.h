#pragma once

#include "Turret.h"



class TurretFactory {
public:
	TurretFactory() {}
	~TurretFactory() {}
	TurretBase* create(const TurretBase &turret);
	BasicTurret* createBasicTurret(const TurretBase &turret);
	MortarTurret* createMortarTurret(const TurretBase &turret);
	BlastTurret* createBlastTurret(const TurretBase &turret);
private:

};

