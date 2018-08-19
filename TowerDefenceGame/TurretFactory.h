#pragma once

#include "Turret.h"



class TurretFactory {
public:
	TurretFactory() {}
	~TurretFactory() {}

	BasicTurret* create(std::string name, double damage, double firerate, double range);

private:

};

BasicTurret* TurretFactory::create(std::string name, double damage, double firerate, double range) {
	return new BasicTurret(name, damage, firerate, range);
}

BlastTurret* TurretFactory::create(std::string name, double damage, double firerate, double range) {

}

MortarTurret* TurretFactory::create(std::string name, double damage, double firerate, double range, double splashdamage, double splashrange, double minrange) {

}



