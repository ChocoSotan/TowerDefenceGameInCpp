#pragma once

#include "Wave.h"
#include "Enemy.h"
#include "Loader.h"
#include "Texture.h"

#include <vector>
#include <string>

class WaveSystem final {
public:
	WaveSystem(short interval_wave, short interval_enemy);
	~WaveSystem();

	void init(std::string filename, const Vector2D &pos);
	void update(std::vector<EnemyBase*> *venemy, long long *resource, const double interest);
	long long getCount() { return this->m_count; }
	void nextWave();
	void draw(const Texture &texture, const Vector2D &pos);

	bool isFinishedSendEnemy() {
		return m_currentwave == (signed)vwave.size() ?  true : false;
	}
	
private:
	std::vector<EnemyBase*> *pvenemy;
	std::vector<Wave*> vwave;
	Texture *texture;

	short m_currentwave;
	
	short m_interval_wave;
	short m_interval_enemy;

	long m_count;

	int m_fonthandle;
};

