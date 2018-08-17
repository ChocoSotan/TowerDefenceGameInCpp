#include "Wave.h"

#include "Enemy.h"

#include <vector>

Wave::Wave(EnemyType type, short number, double hitpoint, short attackpower, double movespeed, long long resourcereward, bool isboss) {
}


Wave::~Wave() {
}

void Wave::execute(std::vector<EnemyBase*> &venemy) {
	for (int i = 0; i < number; i++) {
		switch (type) {
		case Normal:
			break;
		case Fast:
			break;
		case Armored:
			break;
		default:
			break;
		}
		venemy.push_back();
	}
}