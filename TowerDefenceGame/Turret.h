#pragma once



#include <vector>
#include <string>

#include "Vector2D.h"
#include "Enemy.h"
#include "TurretBarrel.h"
#include "Attack.h"
class TargetPriority;
class TurretBase {
public:
	TurretBase(std::string name, double damage, double firerate, double range) {
		this->name = name;
		this->damage = damage;
		this->firerate = firerate;
		this->range = range;
	}
	virtual ~TurretBase() = 0;

	virtual void attack(std::vector<EnemyBase> &targetlist) = 0;
	virtual void construct() = 0;
	bool canConstruct(long long resource);
	virtual void upgrade() = 0;
	bool canUpgrade(long long resource);
	virtual void destroy() = 0;

	std::string getName() const { return this->name; }
	double getDamage() const { return this->damage; }
	double getFireRate() const { return this->firerate; }
	double getRange() const { return this->range; }
	Vector2D getPosition() const { return this->position; }

	void setAttackPower(double damage) { this->damage = damage; }
	void setFireRate(double firerate) { this->firerate = firerate; }
	void setAttackRange(double range) { this->range = range; }
	void setTarget(TargetPriority* priority) {this->target = priority;}
	



protected:

	std::string name;
	int constructcost;
	int upgradecost;
	int costspent;
	double damage;
	double firerate;
	double range;
	Vector2D position;
	TurretBarrel turretbarrel;
	TargetPriority* target;
	int texturehandle;

	
};

/// <summary>
/// BasicTurret Class.
/// </summary>
class BasicTurret : public TurretBase {
public:
	BasicTurret(std::string name, double damage, double firerate, double range) : TurretBase(name, damage, firerate, range) {}
	~BasicTurret() {}

	void attack(std::vector<EnemyBase> &targetlist) override;


protected:

};

/// <summary>
/// Turret that takes splash damage but range is restricted.
/// </summary>
class MortarTurret : public TurretBase {
public:
	MortarTurret(std::string name, double damage, double firerate, double maxrange, double splashdamage, double splashrange, double minrange) : TurretBase(name, damage, firerate, maxrange) {
		this->splashdamage = splashdamage;
		this->splashrange = splashrange;
		this->minrange = minrange;
	}
	~MortarTurret() {}

	void attack(std::vector<EnemyBase> &targetlist) override;

protected:
	double splashdamage;
	double splashrange;
	double minrange;
};

/// <summary>
/// Turret that takes damage to all enemies in range.
/// </summary>
class BlastTurret : public TurretBase {
public:
	BlastTurret(std::string name, double damage, double firerate, double range) : TurretBase(name, damage, firerate, range) {
		
	}
	~BlastTurret() {}

	void attack(std::vector<EnemyBase> &targetlist) override;

protected:
	
};

/// <summary>
/// Turret that takes damage to enemy over time
/// </summary>
class DotTurret : public TurretBase {
public:
	DotTurret(std::string name, double damage, double firerate, double range, double effectvalue) : TurretBase(name, damage, firerate, range) {
		this->effectvalue = effectvalue;
	}

	void attack(std::vector<EnemyBase> &targetlist) override;

protected:
	double effectvalue;

};