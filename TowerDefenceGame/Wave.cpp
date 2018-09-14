#include "Wave.h"

#include "Enemy.h"

#include <vector>

Wave::Wave(std::vector<EnemyBase*> &venemy) {
	for (int i = 0; i < venemy.size(); i++) {
		this->venemy.push_back(venemy[i]);
	}
}


Wave::~Wave() {
}

void Wave::push(std::vector<EnemyBase*> &venemy) {
	for (int i = 0; i < (signed)this->venemy.size(); i++) {
		venemy.push_back(this->venemy[i]);
	}
}