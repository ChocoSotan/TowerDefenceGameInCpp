#include "WaveSystem.h"

#include "Enemy.h"

#include <vector>
#include <fstream>
#include <sstream>


WaveSystem::WaveSystem(std::vector<EnemyBase*> *venemy, short interval) {
	this->venemy = venemy;
	count = 0;
	currentwave = 0;
	this->interval = interval;
}


WaveSystem::~WaveSystem() {
}

void WaveSystem::init(std::string filename) {
	
}

void WaveSystem::update(std::vector<EnemyBase*> &venemy) {
	if (count % interval != 0) {
		count++;
		return;
	}

	vwave[currentwave].execute(venemy);


	currentwave++;
	count++;
}

void WaveSystem::draw() {

}