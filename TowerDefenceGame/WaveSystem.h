#pragma once

#include "Wave.h"
#include "Enemy.h"

#include <vector>

class WaveSystem final {
public:
	WaveSystem(std::vector<EnemyBase*> *venemy, short interval);
	~WaveSystem();

	void init(std::string filename);
	void update(std::vector<EnemyBase*> &venemy);
	void draw();

private:
	std::vector<EnemyBase*> *venemy;
	std::vector<Wave> vwave;
	short currentwave;
	long long count;
	short interval;
};

