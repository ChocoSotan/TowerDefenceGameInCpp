#pragma once

#include "Enemy.h"

#include <vector>


class Wave {
public:
	Wave(const std::vector<EnemyBase*> &venemy);
	~Wave() {}

	void push(std::vector<EnemyBase*> *venemy);
	std::vector<EnemyBase*> getWaveInfo() { return this->venemy; }
	void deleteEnemy() {
		for (auto i = venemy.begin(); i != venemy.end(); ++i) {
			delete (*i);
		}
	}
	
private:
	std::vector<EnemyBase*> venemy;
};

