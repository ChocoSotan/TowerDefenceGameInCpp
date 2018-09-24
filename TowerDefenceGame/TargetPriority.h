#pragma once
#include"Enemy.h"
//#include"Turret.h"
#include"DxLib.h"
class TurretBase;
//class MortarTurret;
class TargetPriority {
public:
	TargetPriority(const std::vector<Vector2D> &vpath) {
		this->vpath = vpath;
	}
	virtual ~TargetPriority() {}
	virtual int decisionOrder(const std::vector<EnemyBase*> &targetlist, TurretBase &turret) const = 0;
protected:
	std::vector<Vector2D> vpath;
};

class ClosestTurret : public TargetPriority {
public:
	ClosestTurret(const std::vector<Vector2D> &vpath) : TargetPriority(vpath) {
		
	}
	int decisionOrder(const std::vector<EnemyBase*> &targetlist, TurretBase &turret) const override;
private:
};


class FarthestTurret : public TargetPriority {
public:
	FarthestTurret(const std::vector<Vector2D> &vpath) : TargetPriority(vpath) {

	}
	int decisionOrder(const std::vector<EnemyBase*> &targetlist, TurretBase &turret) const override;
private:
};


class ClosestBase : public TargetPriority {
public:
	ClosestBase(const std::vector<Vector2D> &vpath) : TargetPriority(vpath) {

	}
	int decisionOrder(const std::vector<EnemyBase*> &targetlist, TurretBase &turret) const override;
private:
};


class FarthestBase : public TargetPriority {
public:
	FarthestBase(const std::vector<Vector2D> &vpath) : TargetPriority(vpath) {

	}
	int decisionOrder(const std::vector<EnemyBase*> &targetlist, TurretBase &turret) const override;
private:
};


class LowestHealth : public TargetPriority {
public:
	LowestHealth(const std::vector<Vector2D> &vpath) : TargetPriority(vpath) {

	}
	int decisionOrder(const std::vector<EnemyBase*> &targetlist, TurretBase &turret) const override;
private:
};


class HighestHealth : public TargetPriority {
public:
	HighestHealth(const std::vector<Vector2D> &vpath) : TargetPriority(vpath) {

	}
	int decisionOrder(const std::vector<EnemyBase*> &targetlist, TurretBase &turret) const override;
private:
};


class Random : public TargetPriority {
public:
	Random(const std::vector<Vector2D> &vpath) : TargetPriority(vpath) {
		SRand(0);
	}
	int decisionOrder(const std::vector<EnemyBase*> &targetlist, TurretBase &turret) const override;
private:
};
//ゲーム自体にコンストラクタを呼ぶ関数があると想定。