#include"TargetPriority.h"
#include"Vector2D.h"

int ClosestTurret::decisionOrder(const std::vector<EnemyBase*> &targetlist, TurretBase &turret) const {
	if (targetlist.empty())return -1;
	double mindistancefromturret = DBL_MAX;
	int targetindex;
	targetindex = -1;
	for (int i = 0; i < (signed)targetlist.size(); i++) {
		if (turret.getRange() < turret.getPosition().getAbsTo(targetlist[i]->getPosition())) continue;
		if (turret.getMinRange() > turret.getPosition().getAbsTo(targetlist[i]->getPosition())) continue;
		if (!targetlist[i]->isAlive())continue;
		if (turret.getPosition().getAbsTo(targetlist[i]->getPosition()) < mindistancefromturret) {
			mindistancefromturret = turret.getPosition().getAbsTo(targetlist[i]->getPosition());
			targetindex = i;
		}
	}
	if (targetindex == -1)return -1;
	return targetindex;
}
int FarthestTurret::decisionOrder(const std::vector<EnemyBase*> &targetlist, TurretBase &turret) const {
	if (targetlist.empty())return -1;
	double maxdistancefromturret = 0;
	int targetindex;
	targetindex = -1;
	for (int i = 0; i < (signed)targetlist.size(); i++) {
		if (turret.getRange() < turret.getPosition().getAbsTo(targetlist[i]->getPosition())) continue;
		if (turret.getMinRange() > turret.getPosition().getAbsTo(targetlist[i]->getPosition())) continue;
		if (!targetlist[i]->isAlive())continue;
		if (turret.getPosition().getAbsTo(targetlist[i]->getPosition()) > maxdistancefromturret) {
			maxdistancefromturret = turret.getPosition().getAbsTo(targetlist[i]->getPosition());
			targetindex = i;
		}
	}
	if (targetindex == -1)return targetindex;
	return targetindex;
}
int ClosestBase::decisionOrder(const std::vector<EnemyBase*> &targetlist, TurretBase &turret) const {
	if (targetlist.empty())return -1;
	double mindistancetobase = DBL_MAX;
	int targetindex;
	targetindex = -1;
	for (auto i = 0; i < (signed)targetlist.size(); i++) {
		if (turret.getRange() < turret.getPosition().getAbsTo(targetlist[i]->getPosition())) continue;
		if (turret.getMinRange() > turret.getPosition().getAbsTo(targetlist[i]->getPosition())) continue;
		if (!targetlist[i]->isAlive())continue;
		if (targetlist[i]->getDistanceToBase(vpath) < mindistancetobase) {
			mindistancetobase = targetlist[i]->getDistanceToBase(vpath);
			targetindex = i;
			break;
		}
	}
	if (targetindex == -1)return targetindex;
	return targetindex;
}
int FarthestBase::decisionOrder(const std::vector<EnemyBase*> &targetlist, TurretBase &turret) const {
	if (targetlist.empty())return -1;
	double maxdistancetobase = 0;
	int targetindex;
	targetindex = -1;
	for (auto i = 0; i < (signed)targetlist.size(); i++) {
		if (turret.getRange() < turret.getPosition().getAbsTo(targetlist[i]->getPosition())) continue;
		if (turret.getMinRange() > turret.getPosition().getAbsTo(targetlist[i]->getPosition())) continue;
		if (!targetlist[i]->isAlive())continue;
		if (targetlist[i]->getDistanceToBase(vpath) < maxdistancetobase) {
			maxdistancetobase = targetlist[i]->getDistanceToBase(vpath);
			targetindex = i;
		}
	}
	if (targetindex == -1)return targetindex;
	return targetindex;
}
int LowestHealth::decisionOrder(const std::vector<EnemyBase*> &targetlist, TurretBase &turret) const {
	if (targetlist.empty())return -1;
	double minHitPoint = DBL_MAX;
	int targetindex;
	targetindex = -1;
	for (int i = 0; i < (signed)targetlist.size(); i++) {
		if (turret.getRange() < turret.getPosition().getAbsTo(targetlist[i]->getPosition())) continue;
		if (turret.getMinRange() > turret.getPosition().getAbsTo(targetlist[i]->getPosition())) continue;
		if (!targetlist[i]->isAlive())continue;
		if (targetlist[i]->getHitpoint() < minHitPoint) {
			minHitPoint = turret.getPosition().getAbsTo(targetlist[i]->getPosition());
			targetindex = i;
		}
	}
	if (targetindex == -1)return targetindex;
	return targetindex;
}
int HighestHealth::decisionOrder(const std::vector<EnemyBase*>&targetlist, TurretBase &turret) const {
	if (targetlist.empty())return -1;
	double maxHitPoint = 0;
	int targetindex;
	targetindex = -1;
	for (int i = 0; i < (signed)targetlist.size(); i++) {
		if (turret.getRange() < turret.getPosition().getAbsTo(targetlist[i]->getPosition())) continue;
		if (turret.getMinRange() > turret.getPosition().getAbsTo(targetlist[i]->getPosition())) continue;
		if (!targetlist[i]->isAlive())continue;
		if (targetlist[i]->getHitpoint() > maxHitPoint) {
			maxHitPoint = turret.getPosition().getAbsTo(targetlist[i]->getPosition());
			targetindex = i;
		}
	}
	if (targetindex == -1)return targetindex;
	return targetindex;
}
int Random::decisionOrder(const std::vector<EnemyBase*> &targetlist, TurretBase &turret) const {
	if (targetlist.empty())return -1;
	int targetindex;
	targetindex = -1;

	for (auto i = 0; i < (signed)targetlist.size(); i++) {
		if (targetlist[i]->getPosition().getAbsTo(turret.getPosition()) < turret.getRange() && targetlist[i]->isAlive())targetindex = i;
	}
	if (targetindex == -1)return targetindex;
	do {
		targetindex = GetRand((int)targetlist.size());
		if (targetlist[targetindex]->getPosition().getAbsTo(turret.getPosition()) < turret.getRange() && targetlist[targetindex]->isAlive())break;
	} while (1);
	return targetindex;
}