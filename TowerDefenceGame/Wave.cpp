#include "Wave.h"

#include "Enemy.h"

#include <vector>

Wave::Wave(const std::vector<EnemyBase*> &venemy) {
	for (int i = 0; i < (signed)venemy.size(); i++) {
		this->venemy.push_back(venemy[i]);
	}
}


void Wave::push(std::vector<EnemyBase*> *venemy) {
	for (int i = 0; i < (signed)this->venemy.size(); i++) {
		venemy->push_back(this->venemy[i]);
	}
}