#include "WaveSystem.h"

#include "Enemy.h"
#include "Loader.h"

#include <vector>
#include <fstream>
#include <sstream>


WaveSystem::WaveSystem(std::vector<EnemyBase*> *venemy, short interval) {
	this->pvenemy = venemy;
	count = 0;
	currentwave = 0;
	this->interval = interval;
}


WaveSystem::~WaveSystem() {
}

void WaveSystem::init(std::string filename, Vector2D &pos) {
	WaveLoader waveloader;
	waveloader.load(filename, this->vwave, pos);
}

void WaveSystem::update(std::vector<EnemyBase*> &venemy) {
	if (vwave.size() == currentwave)return;
	if (count % interval != 0) {
		count++;
		return;
	}

	vwave[currentwave]->push(venemy);


	currentwave++;
	count++;
}


void WaveSystem::nextWave() {
	while (count % interval < interval - 1) {
		count++;
	}
}
