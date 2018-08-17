#pragma once

#include "Enemy.h"

#include <vector>

typedef enum {
	Normal,
	Armored,
	Fast,

}EnemyType;


/// <summary>
/// This class acts as Enemy-Factory
/// </summary>
class Wave {
public:
	Wave(EnemyType type, short number, double hitpoint, short attackpower, double movespeed, long long resourcereward, bool isboss);
	~Wave();

	void execute(std::vector<EnemyBase*> &venemy);

	
private:
	EnemyType type;
	short number;
	double hitpoint;
	short attackpower;
	double movespeed;
	long long resourcereward;
	bool isBoss;

	std::vector<EnemyBase> venemy;
};

