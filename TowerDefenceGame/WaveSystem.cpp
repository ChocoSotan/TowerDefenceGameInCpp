#include "WaveSystem.h"

#include "Enemy.h"
#include "Loader.h"
#include "Vector2D.h"

#include <vector>
#include <fstream>
#include <sstream>


WaveSystem::WaveSystem(std::vector<EnemyBase*> *venemy, short interval, Texture *texture) {
	this->pvenemy = venemy;
	this->texture = texture;
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

void WaveSystem::draw(const Vector2D &pos, std::string filename, std::string fontname, int fontsize) {
	int sx, sy;
	GetGraphSize(texture->getHandle(filename), &sx, &sy);
	for (int i = currentwave; i < (signed)vwave.size(); i++) {
		DrawGraph(pos.getX(), pos.getY() + i * sy, texture->getHandle(filename), FALSE);
		DrawFormatStringToHandle(pos.getX(), pos.getY() + i * sy, GetColor(255, 255, 255), CreateFontToHandle(fontname.c_str(), fontsize, -1, DX_FONTTYPE_ANTIALIASING_EDGE),
			"%d", currentwave + i);
	}
}

Wave WaveSystem::getWaveData(int wave) {
	if (wave < 0 || vwave.size() < wave)return *this->vwave[0];
	return *this->vwave[wave];
}



