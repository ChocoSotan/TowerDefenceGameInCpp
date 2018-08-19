#pragma once
#include"Enemy.h"
#include"Turret.h"
class TurretBase;
class TargetPriority {
public:
	TargetPriority() {

	}
	virtual ~TargetPriority() {}
	virtual int decisionOrder(std::vector<EnemyBase> &targetlist, TurretBase &turret)const=0;
};

class ClosestTurret : public TargetPriority {
public:
	ClosestTurret() {

	}
	int decisionOrder(std::vector<EnemyBase> &targetlist, TurretBase &turret)const override;/* {
		if (targetlist.empty())return -1;
		double mindistancefromturret=DBL_MAX;
		int targetindex=0;
		for (int i = 0; i < targetlist.size(); i++) {
			if (turret.getRange() < turret.getPosition().getAbsTo(targetlist[0].getPosition()))continue;
			if (turret.getPosition().getAbsTo(targetlist[i].getPosition()) < mindistancefromturret) {
				mindistancefromturret = turret.getPosition().getAbsTo(targetlist[i].getPosition());
				targetindex = i;
			}
		}
		return targetindex;
	}*/
private:
};


class FarthestTurret :public TargetPriority {
public:
	int decisionOrder(std::vector<EnemyBase>&targetlist, TurretBase &turret)const override;/* {
		if (targetlist.empty())return -1;
		double maxdistancefromturret;
		int targetindex = 0;
		for (int i = 0; i < targetlist.size(); i++) {
			if (turret.getRange() < turret.getPosition().getAbsTo(targetlist[0].getPosition())) continue;
				if (turret.getPosition().getAbsTo(targetlist[i].getPosition()) > maxdistancefromturret) {
					maxdistancefromturret = turret.getPosition().getAbsTo(targetlist[i].getPosition());
					targetindex = i;
				}
		}
		return targetindex;
	}*/
private:
};


class ClosestBase :public TargetPriority {
public:
	int decisionOrder(std::vector<EnemyBase>&targetlist,TurretBase &turret)const override {

	}
private:
	double mindistancefrombase;
};


class FarthestTrret :public TargetPriority {
public:
	int decisionOrder(std::vector<EnemyBase>&targetlist, TurretBase &turret)const override {

	}
private:
	double maxdistancefrombase;
};


class LowestHealth :public TargetPriority {
public:
	int decisionOrder(std::vector<EnemyBase>&targetlist, TurretBase &turret)const override {

	}
private:
	int minhitpoint;
};


class HighestHealth :public TargetPriority {
public:
	int decisionOrder(std::vector<EnemyBase>&targetlist, TurretBase &turret)const override {

	}
private:
	int maxhitpoint;
};


class Random :public TargetPriority {
public:
	int decisionOrder(std::vector<EnemyBase>&targetlist, TurretBase &turret)const override {

	}
private:
};


//ゲーム自体にコンストラクタを呼ぶ関数があると想定。