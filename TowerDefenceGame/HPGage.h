#pragma once
#include"Enemy.h"
//maxhitpoint���G�l�~�[�����Ă΂����̓��e���ς��B
//�G�l�~�[������������Ƃ�z��B
class HPGage {
public:
	HPGage(double maxhitpoint) {
		this->maxhitpoint = maxhitpoint;
	}
	~HPGage(){}
	void draw(Vector2D,double hitpoint)const;
private:
	double maxhitpoint;
};