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
	void nextWave();
	void draw(const Texture &texture, const Vector2D &pos);

	bool isFinishedSendEnemy() { return m_currentwave == (signed)vwave.size() ?  true : false; }

	// getter
	long long getCount() const { return this->m_count; }
	short getCurrentWave() const { return this->m_currentwave; }
	size_t getMaxWave() const { return this->vwave.size(); }
	size_t getReservedEnemySize() const { return this->vpenemy.size(); }

private:
	std::vector<std::pair<EnemyBase*, short>> vpenemy;

	std::vector<Wave*> vwave;
	Texture *texture;

	short m_currentwave;
	
	short m_interval_wave;
	short m_interval_enemy;

	long m_count;

	int m_fonthandle;
};

