#pragma once

#include "Vector2D.h"
#include "Enemy.h"
#include "TurretBarrel.h"
#include "Texture.h"
#include "Sound.h"

#include <vector>
#include <string>
#include <math.h>

class TargetPriority;

class TurretBase {
public:
	TurretBase(std::string name, std::string type, double damage, double firerate, double range,int constructcost,int upgradecost, Vector2D position) {
		this->name = name;
		this->type = type;
		this->damage = damage;
		this->firerate = firerate;
		this->range = range;
		this->grade = 1;
		this->constructcost = constructcost;
		this->upgradecost = upgradecost;
		this->costspent = constructcost;
		this->position = position;
		this->angle = 0;

		this->waittime = 0;
		this->target = nullptr;
	}
	virtual ~TurretBase() {}

	virtual void attack(std::vector<EnemyBase*> *targetlist, const Sound &sound) = 0;
	bool canConstruct(long long resource) const;
	virtual void upgrade() = 0;
	bool canUpgrade(long long resource) const;
	virtual int destroy() = 0;
	void changePriority(TargetPriority* target);
	virtual void draw(const Texture &texture) const = 0;

	std::string getName() const { return this->name; }
	std::string getType()const { return this->type; }
	double getDamage() const { return this->damage; }
	double getFireRate() const { return this->firerate; }
	double getRange() const { return this->range; }
	double getWaitTime()const { return this->waittime; }
	double getMinRange()const { return this->minrange; }
	int getGrade()const { return this->grade; }
	int getConstructCost()const { return this->constructcost; }
	int getUpgradeCost()const { return this->upgradecost; }
	int getCostSpent()const { return this->costspent; }
	Vector2D getPosition() const { return this->position; }

	void setWaitTime(double waittime) { this->waittime = waittime; }
	void setPosition(const Vector2D &pos) { 
		this->position = pos;
		this->turretbarrel.setPosition(pos);
	}

	virtual const std::string getStatusText() const;

protected:

	std::string name;
	std::string type;
	int constructcost;
	int upgradecost;
	int costspent;
	int grade;
	double damage;
	double firerate;
	double range;
	double waittime;
	double angle;
	double minrange;
	Vector2D position;
	TurretBarrel turretbarrel;
	TargetPriority* target;
};

/// <summary>
/// BasicTurret Class.
/// </summary>
class BasicTurret : public TurretBase {
public:
	BasicTurret(std::string name, std::string type, double damage, double firerate, double range,int constructcost,int upgradecost,Vector2D position) : TurretBase(name, type, damage, firerate, range,constructcost,upgradecost,position) {
		this->minrange = 0;
	}
	~BasicTurret() {}
	void attack(std::vector<EnemyBase*> *targetlist, const Sound &sound) override;
	void upgrade()override;
	void draw(const Texture &texture) const override;
	int destroy()override;

	

protected:
};

/// <summary>
/// Turret that takes splash damage but range is restricted.
/// </summary>
class MortarTurret : public TurretBase {
public:
	MortarTurret(std::string name, std::string type, double damage, double firerate, double maxrange, int constructcost, int upgradecost, Vector2D position, double splashdamage, double splashrange, double minrange) : TurretBase(name, type, damage, firerate, maxrange, constructcost, upgradecost, position) {
		this->splashdamage = splashdamage;
		this->splashrange = splashrange;
		this->minrange = minrange;
	}
	~MortarTurret() {}
	void upgrade()override;
	int destroy()override;
	void attack(std::vector<EnemyBase*> *targetlist, const Sound &sound) override;
	double getSplashDamage() { return this->splashdamage; }
	double getSplashRange() { return this->splashrange; }
	void setSplashDamage(double splashdamage) {this->splashdamage=splashdamage; }
	void setSplashRange(double splashrange) { this->splashrange = splashrange; }
	void setMinRange(double minrange) { this->minrange = minrange; }
	void draw(const Texture &texture) const override;

	const std::string getStatusText() const override;

protected:
	double splashdamage;
	double splashrange;
};

/// <summary>
/// Turret that takes damage to all enemies in range.
/// </summary>
class BlastTurret : public TurretBase {
public:
	BlastTurret(std::string name, std::string type, double damage, double firerate, double range, int constructcost, int upgradecost,Vector2D position) : TurretBase(name, type, damage, firerate, range, constructcost, upgradecost,position) {
		this->minrange = 0;
	}
	virtual ~BlastTurret() {}
	void upgrade()override;
	int destroy()override;
	void attack(std::vector<EnemyBase*> *targetlist, const Sound &sound) override;
	void draw(const Texture &texture) const override;

protected:
	
};

/// <summary>
/// Turret that takes damage to enemy over time
/// </summary>
class DotTurret : public TurretBase {
public:
	DotTurret(std::string name, std::string type, double damage, double firerate, double range, int constructcost, int upgradecost,Vector2D position, double effectvalue) : TurretBase(name, type, damage, firerate, range, constructcost, upgradecost,position) {
		this->effectvalue = effectvalue;
	}
	~DotTurret() {}

	void attack(std::vector<EnemyBase*> *targetlist, const Sound &sound) override;
	void draw(const Texture &texture) const override;

protected:
	double effectvalue;

};