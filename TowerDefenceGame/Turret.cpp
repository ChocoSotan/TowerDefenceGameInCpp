#include "Turret.h"

#include "TargetPriority.h"

// thisが持ってるメンバ変数はget();set();使わないでthis->hogeを使って変更してください

bool TurretBase::canConstruct(long long resource) {
	return resource >= constructcost;
}
bool TurretBase::canUpgrade(long long resource) {
	return resource >= upgradecost;
}

void BasicTurret::attack(std::vector<EnemyBase*> &targetlist) {
	int targetindex;
	targetindex = this->target->decisionOrder(targetlist, *this);
	if (targetindex == -1)return;
	// there is no enemy in stage

	/* attack */
	// set barrel angle to target
	this->turretbarrel.setAngle(this->getPosition().getAngleTo(targetlist[targetindex]->getPosition()));
	// take damage
	targetlist[targetindex]->setHitpoint(targetlist[targetindex]->getHitpoint() - this->damage);

}
void TurretBase::changePriority(TargetPriority* target) {
	delete this->target;
	this->target = target;
}
//レンジ・グレード・ダメージを増加
void BasicTurret::upgrade() {
	this->grade++;
	this->range *= 1.1;
	this->damage *= 1.5;
	this->costspent += upgradecost;
	this->upgradecost = round(this->upgradecost * 1.5);

	// さすがにキレた
	/*setRange(getRange()*1.1);
	setGrade(getGrade() + 1);
	setDamage(getDamage()*1.5);
	setCostSpent(getCostSpent() + getUpgradeCost());
	setUpgradeCost((int)round(getUpgradeCost()*1.5));*/
	return;
}
//費やしたコストに応じてコストを返還
int BasicTurret::destroy() {
	/*return (int)round(getCostSpent()*0.7);*/
	return (int)round(this->costspent * 0.7);
}

void MortarTurret::attack(std::vector<EnemyBase*> &targetlist) {
	//set target
	int targetindex;
	targetindex = this->target->decisionOrder(targetlist, *this);
	if (targetindex == -1)return;
	//set barrel angle
	this->turretbarrel.setAngle(this->position.getAngleTo(targetlist[targetindex]->getPosition()));
	//attack to the target
	targetlist[targetindex]->setHitpoint(targetlist[targetindex]->getHitpoint() - this->damage);
	//splash damage
	for (auto i = 0; i < (signed)targetlist.size(); i++) {
		// ここしっかりして
		/*if (targetlist[targetindex]->getPosition().getAbsTo(targetlist[i]->getPosition()) < this->getSplashRange()) {
			targetlist[i]->setHitpoint(targetlist[i]->getHitpoint() - this->getSplashDamage());
		}*/
		if (targetlist[targetindex]->getPosition().getAbsTo(targetlist[i]->getPosition()) < this->splashrange) {
		targetlist[i]->setHitpoint(targetlist[i]->getHitpoint() - this->splashdamage);
		}
	}
}
void MortarTurret::upgrade() {
	// なおしとけ
	/*setSplashDamage(getSplashDamage()*1.5);
	setSplashRange(getSplashRange()*1.1);
	setRange(getRange()*1.1);
	setGrade(getGrade() + 1);
	setDamage(getDamage()*1.5);
	setCostSpent(getCostSpent() + getUpgradeCost());
	setUpgradeCost((int)round(getUpgradeCost()*1.5));*/
	this->grade++;
	this->splashdamage *= 1.5;
	this->splashrange *= 1.1;
	this->range *= 1.1;
	this->damage *= 1.5;
	this->costspent += this->upgradecost;
	this->upgradecost = (int)round(this->upgradecost * 1.5);
	return;
}
int MortarTurret::destroy() {
	/*return (int)round(getCostSpent()*0.7);*/
	return (int)round(this->costspent * 0.7);
}
void BlastTurret::attack(std::vector<EnemyBase*> &targetlist) {
	for (auto i = 0; i < (signed)targetlist.size(); i++) {
		// ここも頼むから
		if (this->getRange() > this->getPosition().getAbsTo(targetlist[i]->getPosition())) {
			targetlist[i]->setHitpoint(targetlist[i]->getHitpoint() - this->getDamage());
		}
	}
}
void BlastTurret::upgrade() {
	// なおしとけ
	/*setRange(getRange()*1.1);
	setGrade(getGrade() + 1);
	setDamage(getDamage()*1.5);
	setCostSpent(getCostSpent() + getUpgradeCost());
	setUpgradeCost((int)round(getUpgradeCost()*1.5));*/
	this->grade++;
	this->range *= 1.1;
	this->damage *= 1.5;
	this->costspent += upgradecost;
	this->upgradecost = round(this->upgradecost * 1.5);
	return;
}
int BlastTurret::destroy() {
	/*return (int)round(getCostSpent()*0.7);*/
	return (int)round(this->costspent * 0.7);
}