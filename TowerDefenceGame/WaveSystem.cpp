#include "WaveSystem.h"

#include "Enemy.h"
#include "WaveLoader.h"
#include "Vector2D.h"

#include <vector>
#include <fstream>
#include <sstream>


WaveSystem::WaveSystem(short interval) {
	count = 0;
	currentwave = 0;
	this->interval = interval;
	this->fonthandle = CreateFontToHandle("ƒƒCƒŠƒI", 32, 0, DX_FONTTYPE_ANTIALIASING);
}


WaveSystem::~WaveSystem() {
}

void WaveSystem::init(std::string filename, Vector2D &pos) {
	WaveLoader waveloader;
	waveloader.load(filename, this->vwave, pos);
}

void WaveSystem::update(std::vector<EnemyBase*> &venemy, long long *resource) {
	if (vwave.size() == currentwave)return;
	if (count % interval != 0) {
		count++;
		return;
	}

	vwave[currentwave]->push(venemy);
	count = 0;

	*resource *= 1.05;

	count++;
	currentwave++;
}


void WaveSystem::nextWave() {
	while (count % interval < interval - 1) {
		count++;
	}
}

void WaveSystem::draw(const Texture &texture, const Vector2D &pos) {
	std::string filename = "texture/Game/Misc/WaveStone.png";
	int sx, sy;
	GetGraphSize(texture.getHandle(filename), &sx, &sy);

	for (int i = 0; i < (signed)vwave.size() - currentwave; i++) {
		DrawGraph((int)pos.getX(), (int)pos.getY() + i * sy, texture.getHandle(filename), FALSE);

		if (currentwave + i + 1 < 10) {
			DrawFormatStringToHandle((int)pos.getX() + sx / 3, (int)pos.getY() + i * sy + sy / 3 - ((int)count / interval) * sy, GetColor(255, 255, 255),
				this->fonthandle, "%d", currentwave + i + 1);
		}
		else {
			DrawFormatStringToHandle((int)pos.getX() + sx / 5, (int)pos.getY() + i * sy + sy / 3 - ((int)count / interval) * sy, GetColor(255, 255, 255),
				this->fonthandle, "%d", currentwave + i + 1);
		}
	}
}
