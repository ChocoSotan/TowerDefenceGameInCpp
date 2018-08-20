#pragma once

#include "Enemy.h"

#include <vector>


class Wave {
public:
	Wave(std::vector<EnemyBase*> &venemy);
	~Wave();

	void push(std::vector<EnemyBase*> &venemy);

	
private:
	std::vector<EnemyBase*> venemy;
};

