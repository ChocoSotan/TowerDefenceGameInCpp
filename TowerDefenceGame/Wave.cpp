#include "Wave.h"

#include "Enemy.h"

#include <vector>

Wave::Wave() {
}


Wave::~Wave() {
}

void Wave::execute(std::vector<EnemyBase*> &venemy) {
	for (int i = 0; i < this->venemy.size(); i++) {
		venemy.push_back(&this->venemy[i]);
	}
}