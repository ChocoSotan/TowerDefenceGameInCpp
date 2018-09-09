#pragma once

#include "Turret.h"



class TurretFactory {
public:
	TurretFactory() {}
	~TurretFactory() {}
	TurretBase* create(const TurretBase &turret,int channel);
	TurretBase* createBasicTurret(const TurretBase &turret);
	TurretBase* createMortarTurret(const TurretBase &turret);
	TurretBase* createBlastTurret(const TurretBase &turret);

private:

};

