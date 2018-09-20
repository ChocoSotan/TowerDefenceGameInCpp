#pragma once

#include "DxLib.h"

class Keyboard final {
public:
	Keyboard() {}
	~Keyboard() {}


	inline void update();

	// if not pushed, return 0
	inline int getPressingCount(int keycode);
	inline int getReleasingCount(int keycode);



private:
	int m_pressingcount[256];
	int m_releasingcount[256];

};



inline void Keyboard::update() {
	char keystate[256];
	DxLib::GetHitKeyStateAll(keystate);

	for (int i = 0; i < 256; i++) {
		if (keystate[i] != 0) {
			if (m_releasingcount[i] > 0) {
				m_releasingcount[i] = 0;
			}
			m_pressingcount[i]++;
		}
		else {
			if (m_pressingcount[i] > 0) {
				m_pressingcount[i] = 0;
			}
			m_releasingcount[i]++;
		}
	}
}

inline int Keyboard::getPressingCount(int keycode){
	return this->m_pressingcount[keycode];
}

inline int Keyboard::getReleasingCount(int keycode) {
	return this->m_releasingcount[keycode];
}

