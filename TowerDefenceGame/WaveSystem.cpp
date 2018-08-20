#include "WaveSystem.h"

#include "Enemy.h"

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

void WaveSystem::init(std::string filename) {
	wl.load(filename, this->vwave);
}

void WaveSystem::update(std::vector<EnemyBase*> &venemy) {
	if (count % interval != 0) {
		count++;
		return;
	}

	vwave[currentwave]->push(venemy);


	currentwave++;
	count++;
}

void WaveSystem::draw() {

}