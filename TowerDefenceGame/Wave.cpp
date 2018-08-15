#include "Wave.h"

#include "Enemy.h"

#include <vector>

Wave::Wave(EnemyType type, short number, double hitpoint, short attackpower, double movespeed, long long resourcereward, bool isboss) {
}


Wave::~Wave() {
}

std::vector<EnemyBase*> Wave::execute() {
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