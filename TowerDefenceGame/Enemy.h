#pragma once

#include "Vector2D.h"
#include "DxLib.h"

#include <vector>

class EnemyBase {
public:
	EnemyBase(double hitpoint, double movespeed, long attackpower, long long resourcereward) {
		this->hitpoint = hitpoint;
		this->movespeed = movespeed;
		this->attackpower = attackpower;
		this->resourcereward = resourcereward;
		this->currentpoint = 0;
		this->angle = 0;
		this->knockback = 0;
	}
	virtual ~EnemyBase() {}

	virtual void move(std::vector<Vector2D> &vpath) = 0;
	bool loadTexture(const char *filename);
	bool isAlive() const { return hitpoint > 0; }

	double getHitpoint() const			{ return this->hitpoint; }
	double getMovespeed() const			{ return this->movespeed; }
	long getAttackpower() const			{ return this->attackpower; }
	long long getResourcereward() const { return this->resourcereward; }
	Vector2D getPosition() const		{ return this->position; }
	double getAngle() const				{ return this->angle; }
	double getKnockback()const			{ return this->knockback; }

	// for debug
	int getCurrentpoint()const { return this->currentpoint; }

	void setHitpoint(double hitpoint)		{ this->hitpoint = hitpoint; }
	void setMovespeed(double movespeed)		{ this->movespeed = movespeed; }
	void setPosition(Vector2D &position)	{ this->position = position; }
	void setAngle(double angle)				{ this->angle = angle; }

	void setKnockback(double value)			{ this->knockback = knockback; }

protected:
	double hitpoint;
	double movespeed;
	long attackpower;
	long long resourcereward;
	Vector2D position;

	double angle;
	int currentpoint;
	double knockback;

	int texturehandle;
};


class NormalEnemy : public EnemyBase {
public:
	NormalEnemy(double hitpoint, double movespeed, long attackpower, long long resourcereward) : EnemyBase(hitpoint, movespeed, attackpower, resourcereward) {}
	~NormalEnemy();

	void move(std::vector<Vector2D> &vpath) override;


protected:


};