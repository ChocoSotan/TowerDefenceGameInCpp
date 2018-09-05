#include "Turret.h"

#include "TargetPriority.h"

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
void BasicTurret::draw(Texture *texture) {
	DrawGraph(position.getX(), position.getY(), texture->getHandle("texture/Game/Turrets/TuretBases/BasicTurret.png"), TRUE);
	turretbarrel.draw(position.getX(), position.getY(),texture);
}
//レンジ・グレード・ダメージを増加
void BasicTurret::upgrade() {
	this->grade++;
	this->range *= 1.1;
	this->damage *= 1.5;
	this->costspent += upgradecost;
	this->upgradecost = round(this->upgradecost * 1.5);
	return;
}

//費やしたコストに応じてコストを返還
int BasicTurret::destroy() {
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
		if (targetlist[targetindex]->getPosition().getAbsTo(targetlist[i]->getPosition()) < this->splashrange) {
			targetlist[i]->setHitpoint(targetlist[i]->getHitpoint() - this->splashdamage);
		}
	}
}
void MortarTurret::upgrade() {
	this->grade++;
	this->splashdamage *= 1.5;
	this->splashrange *= 1.1;
	this->range *= 1.1;
	this->damage *= 1.5;
	this->costspent += this->upgradecost;
	this->upgradecost = (int)round(this->upgradecost * 1.5);
	return;
}
void MortarTurret::draw(Texture *texture) {
	DrawGraph(position.getX(), position.getY(), texture->getHandle("texture/Game/Turrets/TurretBases/MortarTurret.png"), TRUE);
	turretbarrel.draw(position.getX(), position.getY(), texture);
}
int MortarTurret::destroy() {
	return (int)round(this->costspent * 0.7);
}
void BlastTurret::attack(std::vector<EnemyBase*> &targetlist) {
	for (auto i = 0; i < (signed)targetlist.size(); i++) {
		if (this->range > this->position.getAbsTo(targetlist[i]->getPosition())) {
			targetlist[i]->setHitpoint(targetlist[i]->getHitpoint() - this->damage);
		}
	}
}
void BlastTurret::upgrade() {
	this->grade++;
	this->range *= 1.1;
	this->damage *= 1.5;
	this->costspent += upgradecost;
	this->upgradecost = round(this->upgradecost * 1.5);
	return;
}
void BlastTurret::draw(Texture *texture) {
	DrawGraph(position.getX(), position.getY(), texture->getHandle("texture/Game/Turrets/TuretBases/BlastTurret.png"), TRUE);
	turretbarrel.draw(position.getX(), position.getY(), texture);
}
int BlastTurret::destroy() {
	return (int)round(this->costspent * 0.7);
}