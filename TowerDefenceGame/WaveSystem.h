#pragma once

#include "Wave.h"
#include "Enemy.h"

#include <vector>

class WaveSystem final {
public:
	WaveSystem();
	~WaveSystem();

	bool init();
	void update(std::vector<EnemyBase*> &venemy);
	void draw();
	bool finalize();

private:
	std::vector<Wave> vwaves;
	short currentwave;
	long long count;
	short interval;
};

