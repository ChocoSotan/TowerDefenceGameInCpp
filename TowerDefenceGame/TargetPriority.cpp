#include"TargetPriority.h"
#include"Vector2D.h"

int ClosestTurret::decisionOrder(std::vector<EnemyBase*>& targetlist, TurretBase &turret)const {
	if (turret.getFireRate() > turret.getWaitTime()) {
		turret.setWaitTime(turret.getWaitTime() + 1.0);
		return -1;
	}
	if (targetlist.empty())return -1;
	double mindistancefromturret = DBL_MAX;
	int targetindex;
	targetindex = -1;
	for (int i = 0; i < targetlist.size(); i++) {
		if (turret.getRange() < turret.getPosition().getAbsTo(targetlist[i]->getPosition())) continue;
		if (turret.getMinRange() > turret.getPosition().getAbsTo(targetlist[i]->getPosition())) continue;
		if (turret.getPosition().getAbsTo(targetlist[i]->getPosition()) < mindistancefromturret) {
			mindistancefromturret = turret.getPosition().getAbsTo(targetlist[i]->getPosition());
			targetindex = i;
		}
	}
	if (targetindex == -1)return -1;
	turret.setWaitTime(0.0);
	return targetindex;
}
int FarthestTurret::decisionOrder(std::vector<EnemyBase*>&targetlist, TurretBase &turret)const {
	if (turret.getFireRate() > turret.getWaitTime()) {
		turret.setWaitTime(turret.getWaitTime() + 1.0);
		return -1;
	}
	if (targetlist.empty())return -1;
	double maxdistancefromturret = 0;
	int targetindex;
	targetindex = -1;
	for (int i = 0; i < targetlist.size(); i++) {
		if (turret.getRange() < turret.getPosition().getAbsTo(targetlist[i]->getPosition())) continue;
		if (turret.getMinRange() > turret.getPosition().getAbsTo(targetlist[i]->getPosition())) continue;
		if (turret.getPosition().getAbsTo(targetlist[i]->getPosition()) > maxdistancefromturret) {
			maxdistancefromturret = turret.getPosition().getAbsTo(targetlist[i]->getPosition());
			targetindex = i;
		}
	}
	if (targetindex == -1)return targetindex;
	turret.setWaitTime(0.0);
	return targetindex;
}
int ClosestBase::decisionOrder(std::vector<EnemyBase*>&targetlist, TurretBase &turret)const {
	if (turret.getFireRate() > turret.getWaitTime()) {
		turret.setWaitTime(turret.getWaitTime() + 1.0);
		return -1;
	}
	if (targetlist.empty())return -1;
	double mindistancetobase = DBL_MAX;
	int targetindex;
	targetindex = -1;
	for (auto i = 0; i < targetlist.size(); i++) {
		if (turret.getRange() < turret.getPosition().getAbsTo(targetlist[i]->getPosition())) continue;
		if (turret.getMinRange() > turret.getPosition().getAbsTo(targetlist[i]->getPosition())) continue;
		if (targetlist[i]->getDistanceToBase(vpath) < mindistancetobase) {
			targetindex = i;
		}
	}
	if (targetindex == -1)return targetindex;
	turret.setWaitTime(0.0);
	return targetindex;
}
int FarthestBase::decisionOrder(std::vector<EnemyBase*>&targetlist, TurretBase &turret)const {
	if (turret.getFireRate() > turret.getWaitTime()) {
		turret.setWaitTime(turret.getWaitTime() + 1.0);
		return -1;
	}
	if (targetlist.empty())return -1;
	double maxdistancetobase = 0;
	int targetindex;
	targetindex = -1;
	for (auto i = 0; i < targetlist.size(); i++) {
		if (turret.getRange() < turret.getPosition().getAbsTo(targetlist[i]->getPosition())) continue;
		if (turret.getMinRange() > turret.getPosition().getAbsTo(targetlist[i]->getPosition())) continue;
		if (targetlist[i]->getDistanceToBase(vpath) < maxdistancetobase) {
			targetindex = i;
		}
	}
	if (targetindex == -1)return targetindex;
	turret.setWaitTime(0.0);
	return targetindex;
}
int LowestHealth::decisionOrder(std::vector<EnemyBase*>&targetlist, TurretBase &turret)const {
	if (turret.getFireRate() > turret.getWaitTime()) {
		turret.setWaitTime(turret.getWaitTime() + 1.0);
		return -1;
	}
	if (targetlist.empty())return -1;
	double minHitPoint = DBL_MAX;
	int targetindex;
	targetindex = -1;
	for (int i = 0; i < targetlist.size(); i++) {
		if (turret.getRange() < turret.getPosition().getAbsTo(targetlist[i]->getPosition())) continue;
		if (turret.getMinRange() > turret.getPosition().getAbsTo(targetlist[i]->getPosition())) continue;
		if (targetlist[i]->getHitpoint() < minHitPoint) {
			minHitPoint = turret.getPosition().getAbsTo(targetlist[i]->getPosition());
			targetindex = i;
		}
	}
	if (targetindex == -1)return targetindex;
	turret.setWaitTime(0.0);
	return targetindex;
}
int HighestHealth::decisionOrder(std::vector<EnemyBase*>&targetlist, TurretBase &turret)const {
	if (turret.getFireRate() > turret.getWaitTime()) {
		turret.setWaitTime(turret.getWaitTime() + 1.0);
		return -1;
	}
	if (targetlist.empty())return -1;
	double maxHitPoint = 0;
	int targetindex;
	targetindex = -1;
	for (int i = 0; i < targetlist.size(); i++) {
		if (turret.getRange() < turret.getPosition().getAbsTo(targetlist[i]->getPosition())) continue;
		if (turret.getMinRange() > turret.getPosition().getAbsTo(targetlist[i]->getPosition())) continue;
		if (targetlist[i]->getHitpoint() > maxHitPoint) {
			maxHitPoint = turret.getPosition().getAbsTo(targetlist[i]->getPosition());
			targetindex = i;
		}
	}
	if (targetindex == -1)return targetindex;
	turret.setWaitTime(0.0);
	return targetindex;
}
int Random::decisionOrder(std::vector<EnemyBase*>&targetlist, TurretBase &turret)const {
	if (turret.getFireRate() > turret.getWaitTime()) {
		turret.setWaitTime(turret.getWaitTime() + 1.0);
		return -1;
	}
	if (targetlist.empty())return -1;
	int targetindex;
	targetindex = -1;

	for (auto i = 0; i < targetlist.size(); i++) {
		if (targetlist[i]->getPosition().getAbsTo(turret.getPosition()) < turret.getRange())targetindex = i;
	}
	if (targetindex == -1)return targetindex;
	do {
		targetindex = GetRand((int)targetlist.size());
		if (targetlist[targetindex]->getPosition().getAbsTo(turret.getPosition()) < turret.getRange())break;
	} while (1);
	turret.setWaitTime(0.0);
	return targetindex;
}