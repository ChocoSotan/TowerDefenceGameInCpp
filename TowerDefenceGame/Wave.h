#pragma once

#include "Enemy.h"

#include <vector>


class Wave {
public:
	Wave(std::vector<EnemyBase*> &venemy);
	~Wave() {}

	void push(std::vector<EnemyBase*> &venemy);
	std::vector<EnemyBase*> getWaveInfo() { return this->venemy; }
	
private:
	std::vector<EnemyBase*> venemy;
};

