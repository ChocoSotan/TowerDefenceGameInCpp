
//#include <vector>
#include "Turret.h"

bool TurretBase::canConstruct(long long resource) {
	return resource >= constructcost;
}
bool TurretBase::canUpgrade(long long resource) {
	return resource >= upgradecost;
}

void BasicTurret::attack(std::vector<EnemyBase> &targetlist) {
	int targetindex;
	//targetindex = this->target->decisionOrder(targetlist, *this);
	// there is no enemy in stage
	if (targetlist.size() == 0)return;

	

	/* attack */
	// set barrel angle to target
	//this->turretbarrel.setAngle(this->getPosition().getAngleTo(targetlist[targetindex].getPosition()));
	// take damage
	//targetlist[targetindex].setHitpoint(targetlist[targetindex].getHitpoint() - this->damage);

}

