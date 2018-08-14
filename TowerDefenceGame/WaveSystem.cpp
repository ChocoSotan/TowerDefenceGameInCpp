#include "WaveSystem.h"



WaveSystem::WaveSystem() {
	count = 0;
}


WaveSystem::~WaveSystem() {
}

void WaveSystem::update() {
	static const int interval = 600;
	if (count % interval != 0)return;



	count++;
}

void WaveSystem::draw() {

}