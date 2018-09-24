#include "WaveSystem.h"

#include "Enemy.h"
#include "WaveLoader.h"
#include "Vector2D.h"

#include <vector>
#include <fstream>
#include <sstream>

#include "Debugger.h"


WaveSystem::WaveSystem(short interval_wave, short interval_enemy) {
	m_count = 0;
	m_currentwave = 0;
	this->m_interval_wave = interval_wave;
	this->m_interval_enemy = interval_enemy;
	this->m_fonthandle = CreateFontToHandle("ƒƒCƒŠƒI", 36, 4, DX_FONTTYPE_ANTIALIASING);
}


WaveSystem::~WaveSystem() {
}

void WaveSystem::init(const std::string &filename, const Vector2D &pos) {
	WaveLoader waveloader;
	waveloader.load(filename, this->vwave, pos);
}

void WaveSystem::update(std::vector<EnemyBase*> *venemy, long long *resource, const double interest) {
	if (vwave.empty() && this->vpenemy.empty())return;

	for (int i = 0; i < vpenemy.size(); i++) {
		if (vpenemy[i].second <= 0) {
			venemy->push_back(vpenemy[i].first);
			vpenemy.erase(vpenemy.begin() + i);
		}
		else {
			vpenemy[i].second--;
		}
	}

	if (m_count % m_interval_wave != 0 || m_count == 0) {
		m_count++;
		return;
	}

	std::vector<EnemyBase*> tv;
	//vwave[m_currentwave]->push(&tv);
	(*vwave.begin())->push(&tv);

	delete *vwave.begin();
	vwave.erase(vwave.begin());
	

	for (int i = 0; i < (signed)tv.size(); i++) {
		this->vpenemy.push_back(std::make_pair(tv[i], i * m_interval_enemy));
	}

	

	// nextwave
	*resource = (long long)(*resource * interest);
	m_count = 0;
	m_currentwave++;

	Debugger dbg;
	std::stringstream ss;
	ss << (int)this->vwave.size();
	dbg.print(ss.str());
}


void WaveSystem::nextWave() {
	if (vwave.empty())return;
	while (m_count % m_interval_wave < m_interval_wave - 1) {
		m_count++;
	}
}

void WaveSystem::draw(const Texture &texture, const Vector2D &pos) {
	std::string filename = "texture/Game/Misc/WaveStone.png";
	int sx, sy;
	GetGraphSize(texture.getHandle(filename), &sx, &sy);

	for (int i = 0; i < (signed)vwave.size(); i++) {
		DrawGraph((int)pos.getX(), (int)pos.getY() + (i + 1) * sy - (sy * m_count / m_interval_wave), texture.getHandle(filename), FALSE);

		if (m_currentwave + i < 9) {
			DrawFormatStringToHandle((int)pos.getX() + sx / 3, (int)pos.getY() + (i + 1) * sy + sy / 3 - (sy * m_count / m_interval_wave), GetColor(255, 255, 255),
				this->m_fonthandle, "%d", m_currentwave + i + 1);
		}
		else {
			DrawFormatStringToHandle((int)pos.getX() + sx / 5, (int)pos.getY() + (i + 1) * sy + sy / 3 - (sy * m_count / m_interval_wave), GetColor(255, 255, 255),
				this->m_fonthandle, "%d", m_currentwave + i + 1);
		}
	}
}
