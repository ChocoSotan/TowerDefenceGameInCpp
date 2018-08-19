#pragma once

#include "Enemy.h"

#include <vector>


class Wave {
public:
	Wave();
	~Wave();

	void init();
	void execute(std::vector<EnemyBase*> &venemy);

	
private:
	std::vector<EnemyBase> venemy;
};

