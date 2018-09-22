#pragma once

#include "Wave.h"
#include "Enemy.h"
#include "Loader.h"
#include "Texture.h"

#include <vector>
#include <string>

class WaveSystem final {
public:
	WaveSystem(short interval);
	~WaveSystem();

	void init(std::string filename, Vector2D &pos);
	void update(std::vector<EnemyBase*> &venemy, long long *resource);
	long long getCount() { return this->count; }
	void nextWave();
	void draw(const Texture &texture, const Vector2D &pos);

	bool isFinishedSendEnemy() {
		return currentwave == (signed)vwave.size() ?  true : false;
	}
	
private:
	std::vector<EnemyBase*> *pvenemy;
	std::vector<Wave*> vwave;
	Texture *texture;

	short currentwave;
	
	short interval;

	long count;

	int fonthandle;
};

