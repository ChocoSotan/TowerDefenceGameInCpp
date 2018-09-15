#include "Turret.h"

#include "TargetPriority.h"

#include <sstream>
#include <string>
#include <iomanip>

bool TurretBase::canConstruct(long long resource) const {
	return resource >= constructcost;
}

bool TurretBase::canUpgrade(long long resource) const {
	return resource >= upgradecost;
}

void TurretBase::changePriority(TargetPriority* target) {
	//if(this->target != nullptr) delete this->target;
	this->target = target;
}

const std::string TurretBase::getStatusText() const {
	std::stringstream ss;
	ss	<< this->name << "\n\n"
		<< "Type : " << this->type << "\n\n"
		<< "Cost : " << this->constructcost << "\n\n"
		<< "Damage : " << this->damage << "\n\n"
		<< "FireRate : " << this->firerate << "\n\n"
		<< "Range : " << this->range;
	return ss.str();
}

void BasicTurret::attack(std::vector<EnemyBase*> *targetlist) {
	int targetindex;
	targetindex = this->target->decisionOrder(*targetlist, *this);
	if (targetindex == -1)return;
	// there is no enemy in stage

	/* attack */
	// set barrel angle to target
	this->angle = getPosition().getAngleTo((*targetlist)[targetindex]->getPosition());
	this->turretbarrel.update(this->angle, this->position);

	// take damage
	(*targetlist)[targetindex]->setHitpoint((*targetlist)[targetindex]->getHitpoint() - this->damage);

}

void BasicTurret::draw(const Texture &texture) const {
	const std::vector<std::string> basicturretnames = {
		"BasicTurret", "MachinegunTurret", "SniperTurret",
	};
	
	std::string basepath = "texture/Game/Turrets/TurretBases/";
	std::string barrelpath = "texture/Game/Turrets/TurretBarrels/";

	for (int i = 0; i < (signed)basicturretnames.size(); i++) {
		if (this->name.compare(basicturretnames[i]) == 0) {
			basepath += basicturretnames[i];
			basepath += ".png";
			barrelpath += basicturretnames[i];
			barrelpath += "Barrel.png";
		}
	}

	DrawRotaGraph((int)position.getX(), (int)position.getY(), 1.0, angle, texture.getHandle(basepath), TRUE);
	turretbarrel.draw(texture, barrelpath);
}

//レンジ・グレード・ダメージを増加
void BasicTurret::upgrade() {
	this->grade++;
	this->range *= 1.1;
	this->damage *= 1.5;
	this->costspent += upgradecost;
	this->upgradecost = (int)round(this->upgradecost * 1.5);
}

//費やしたコストに応じてコストを返還
int BasicTurret::destroy() {
	return (int)round(this->costspent * 0.7);
}

void MortarTurret::attack(std::vector<EnemyBase*> *targetlist) {
	//set target
	int targetindex;
	targetindex = this->target->decisionOrder(*targetlist, *this);
	if (targetindex == -1)return;

	// set barrel angle
	this->angle = getPosition().getAngleTo((*targetlist)[targetindex]->getPosition());
	turretbarrel.update(this->angle, this->position);

	//attack to the target
	(*targetlist)[targetindex]->setHitpoint((*targetlist)[targetindex]->getHitpoint() - this->damage);

	//splash damage
	for (auto i = 0; i < (signed)targetlist->size(); i++) {
		if ((*targetlist)[targetindex]->getPosition().getAbsTo((*targetlist)[i]->getPosition()) < this->splashrange) {
			(*targetlist)[i]->setHitpoint((*targetlist)[i]->getHitpoint() - this->splashdamage);
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

void MortarTurret::draw(const Texture &texture) const {
	const std::vector<std::string> splashturretnames = {
		"CanonTurret","MortarTurret",
	};

	std::string basepath = "texture/Game/Turrets/TurretBases/";
	std::string barrelpath = "texture/Game/Turrets/TurretBarrels/";

	for (int i = 0; i < (signed)splashturretnames.size(); i++) {
		if (this->name.compare(splashturretnames[i]) == 0) {
			basepath += splashturretnames[i];
			basepath += ".png";
			barrelpath += splashturretnames[i];
			barrelpath += "Barrel.png";
		}
	}

	DrawRotaGraph((int)position.getX(), (int)position.getY(), 1.0, angle, texture.getHandle(basepath), TRUE);
	turretbarrel.draw(texture, barrelpath);
}

int MortarTurret::destroy() {
	return (int)round(this->costspent * 0.7);
}

const std::string MortarTurret::getStatusText() const {
	std::stringstream ss;
	ss << this->name << "\n\n"
		<< "Type : " << this->type << "\n\n"
		<< "Cost : " << this->constructcost << "\n\n"
		<< "Damage : " << this->damage << "\n\n"
		<< "FireRate : " << this->firerate << "\n\n"
		<< "Range : " << this->range << "\n\n"
		<< "SplashDamage : " << this->splashdamage << "\n\n"
		<< "SplashRange : " << this->splashrange << "\n\n";
	if (minrange != 0) {
		ss << "MinRange : " << this->minrange << "\n\n";
	}
	return ss.str();
}

void BlastTurret::attack(std::vector<EnemyBase*> *targetlist) {
	for (auto i = 0; i < (signed)targetlist->size(); i++) {
		if (this->range > this->position.getAbsTo((*targetlist)[i]->getPosition())) {
			(*targetlist)[i]->setHitpoint((*targetlist)[i]->getHitpoint() - this->damage);
		}
	}
}

void BlastTurret::upgrade() {
	this->grade++;
	this->range *= 1.1;
	this->damage *= 1.5;
	this->costspent += upgradecost;
	this->upgradecost = (int)round(this->upgradecost * 1.5);
	return;
}

void BlastTurret::draw(const Texture &texture) const {
	DrawRotaGraph((int)position.getX(), (int)position.getY(), 1.0, angle, texture.getHandle("texture/Game/Turrets/TurretBases/BlastTurret.png"), TRUE);
	turretbarrel.draw(texture, "texture/Game/Turrets/TurretBarrels/BlastTurretBarrel.png");
}

int BlastTurret::destroy() {
	return (int)round(this->costspent * 0.7);
}