#pragma once
#include "Wave.h"
#include <vector>

class WaveSystem final {
public:
	WaveSystem();
	~WaveSystem();

	bool init();
	void update();
	void draw();
	bool finalize();

private:
	std::vector<Wave> vwaves;
	long long count;
};

