#pragma once

#include "Wave.h"
#include "Enemy.h"
#include "Loader.h"
#include "Texture.h"

#include <vector>

class WaveSystem final {
public:
	WaveSystem(std::vector<EnemyBase*> *venemy, short interval, Texture *texture);
	~WaveSystem();

	void init(std::string filename, Vector2D &pos);
	void update(std::vector<EnemyBase*> &venemy);
	long long getCount() { return this->count; }
	void nextWave();
	void draw(const Vector2D &pos, std::string filename, std::string font, int size);
	Wave getWaveData(int wave);
	
private:
	std::vector<EnemyBase*> *pvenemy;
	std::vector<Wave*> vwave;
	Texture *texture;

	short currentwave;
	long long count;
	short interval;
};

