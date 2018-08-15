#include "WaveSystem.h"



WaveSystem::WaveSystem() {
	count = 0;
	currentwave = 1;
	interval = 600;
}


WaveSystem::~WaveSystem() {
}

void WaveSystem::update(std::vector<EnemyBase*> &venemy) {
	if (count % interval != 0 || count == 0) {
		count++;
		return;
	}
	
	


	currentwave++;
	count++;
}

void WaveSystem::draw() {

}