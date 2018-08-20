#pragma once

#include "Wave.h"
#include "Enemy.h"
#include "Loader.h"

#include <vector>

class WaveSystem final {
public:
	WaveSystem(std::vector<EnemyBase*> *venemy, short interval);
	~WaveSystem();

	void init(std::string filename);
	void update(std::vector<EnemyBase*> &venemy);
	void draw();

private:
	WaveLoader wl;
	std::vector<EnemyBase*> *pvenemy;
	std::vector<Wave*> vwave;
	short currentwave;
	long long count;
	short interval;
};

