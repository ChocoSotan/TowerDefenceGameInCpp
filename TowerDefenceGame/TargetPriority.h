#pragma once

#include "Enemy.h"
#include "Turret.h"
#include "DxLib.h"

class TurretBase;
class MortarTurret;

class TargetPriority {
public:
	TargetPriority(std::vector<Vector2D> &vpath) {
		this->vpath = vpath;
	}
	virtual ~TargetPriority() {}
	virtual int decisionOrder(std::vector<EnemyBase*> &targetlist, TurretBase &turret)const=0;
protected:
	std::vector<Vector2D> vpath;
};

class ClosestTurret : public TargetPriority {
public:
	ClosestTurret(std::vector<Vector2D> &vpath): TargetPriority(vpath) {}
	~ClosestTurret() {}

	int decisionOrder(std::vector<EnemyBase*> &targetlist, TurretBase &turret)const override;
private:
};


class FarthestTurret :public TargetPriority {
public:
	FarthestTurret(std::vector<Vector2D> &vpath) : TargetPriority(vpath) {}
	~FarthestTurret() {}

	int decisionOrder(std::vector<EnemyBase*> &targetlist, TurretBase &turret)const override;
private:
};


class ClosestBase :public TargetPriority {
public:
	ClosestBase(std::vector<Vector2D> &vpath) : TargetPriority(vpath) {}
	~ClosestBase() {}

	int decisionOrder(std::vector<EnemyBase*> &targetlist, TurretBase &turret)const override;
private:
};


class FarthestBase :public TargetPriority {
public:
	FarthestBase(std::vector<Vector2D> &vpath) : TargetPriority(vpath) {}
	~FarthestBase() {}

	int decisionOrder(std::vector<EnemyBase* >&targetlist, TurretBase &turret)const override;
private:
};


class LowestHealth :public TargetPriority {
public:
	LowestHealth(std::vector<Vector2D> &vpath) : TargetPriority(vpath) {}
	~LowestHealth() {}

	int decisionOrder(std::vector<EnemyBase*> &targetlist, TurretBase &turret)const override;
private:
};


class HighestHealth :public TargetPriority {
public:
	HighestHealth(std::vector<Vector2D> &vpath) : TargetPriority(vpath) {}
	~HighestHealth() {}

	int decisionOrder(std::vector<EnemyBase*> &targetlist, TurretBase &turret)const override;
private:
};


class Random :public TargetPriority {
public:
	Random(std::vector<Vector2D> &vpath) : TargetPriority(vpath) {}
	~Random() {}

	int decisionOrder(std::vector<EnemyBase*> &targetlist, TurretBase &turret)const override;
private:
};
//ゲーム自体にコンストラクタを呼ぶ関数があると想定。