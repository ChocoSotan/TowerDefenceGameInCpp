#include "WaveSystem.h"

#include "Enemy.h"
#include "WaveLoader.h"
#include "Vector2D.h"

#include <vector>
#include <fstream>
#include <sstream>


WaveSystem::WaveSystem(short interval_wave, short interval_enemy) {
	m_count = 0;
	m_currentwave = 0;
	this->m_interval_wave = interval_wave;
	this->m_interval_enemy = interval_enemy;
	this->m_fonthandle = CreateFontToHandle("ƒƒCƒŠƒI", 36, 4, DX_FONTTYPE_ANTIALIASING);
}


WaveSystem::~WaveSystem() {
}

void WaveSystem::init(std::string filename, const Vector2D &pos) {
	WaveLoader waveloader;
	waveloader.load(filename, this->vwave, pos);
}

void WaveSystem::update(std::vector<EnemyBase*> *venemy, long long *resource, const double interest) {
	if (vwave.size() == m_currentwave)return;
	if (m_count % m_interval_wave != 0) {
		m_count++;
		return;
	}

	vwave[m_currentwave]->push(venemy);
	m_count = 0;

	*resource = (long long)(*resource * interest);

	m_count++;
	m_currentwave++;
}


void WaveSystem::nextWave() {
	while (m_count % m_interval_wave < m_interval_wave - 1) {
		m_count++;
	}
}

void WaveSystem::draw(const Texture &texture, const Vector2D &pos) {
	std::string filename = "texture/Game/Misc/WaveStone.png";
	int sx, sy;
	GetGraphSize(texture.getHandle(filename), &sx, &sy);

	for (int i = 0; i < (signed)vwave.size() - m_currentwave; i++) {
		DrawGraph((int)pos.getX(), (int)pos.getY() + i * sy, texture.getHandle(filename), FALSE);

		if (m_currentwave + i + 1 < 10) {
			DrawFormatStringToHandle((int)pos.getX() + sx / 3, (int)pos.getY() + i * sy + sy / 3 - ((int)m_count / m_interval_wave) * sy, GetColor(255, 255, 255),
				this->m_fonthandle, "%d", m_currentwave + i + 1);
		}
		else {
			DrawFormatStringToHandle((int)pos.getX() + sx / 5, (int)pos.getY() + i * sy + sy / 3 - ((int)m_count / m_interval_wave) * sy, GetColor(255, 255, 255),
				this->m_fonthandle, "%d", m_currentwave + i + 1);
		}
	}
}
