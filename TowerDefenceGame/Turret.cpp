
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
	targetindex = this->target->decisionOrder(targetlist, *this);
	// there is no enemy in stage

	/* attack */
	// set barrel angle to target
	this->turretbarrel.setAngle(this->getPosition().getAngleTo(targetlist[targetindex].getPosition()));
	// take damage
	targetlist[targetindex].setHitpoint(targetlist[targetindex].getHitpoint() - this->damage);

}//���ꂢ�邩�H���ݎ��ɔ�������G�t�F�N�g��ݒ肷��H
void BasicTurret::construct() {
	return;
}
//�A�b�v�O���[�h�Ƃ��̍ۂ̃G�t�F�N�g��S���B
void BasicTurret::upgrade() {
}
//�j�������u�Ԃ̃G�t�F�N�g��ݒ肷��H
void BasicTurret::destroy() {
	
}

void MortarTurret::attack(std::vector<EnemyBase> &targetlist) {
	//set target
	int targetindex;
	targetindex = this->target->decisionOrder(targetlist, *this);
	//set barrel angle
	this->turretbarrel.setAngle(this->getPosition().getAngleTo(targetlist[targetindex].getPosition()));
	//attack to the target
	targetlist[targetindex].setHitpoint(targetlist[targetindex].getHitpoint() - this->damage);
	//splash damage
	for (auto i = 0; i < targetlist.size(); i++) {
		if (targetlist[targetindex].getPosition().getAbsTo(targetlist[i].getPosition()) < this->getSplashRange()) {
			targetlist[i].setHitpoint(targetlist[i].getHitpoint() - this->getSplashDamage());
		}
	}
}