#pragma once
#include"Enemy.h"
//�G�l�~�[���e�������Ă��邱�Ƃ�z��B
//�G�̍ő�HP�ƌ���HP���K�v�B
class HPGage {
public:
	HPGage() {

	}
	~HPGage(){}
	void draw(Vector2D,double maxhitpoint,double hitpoint)const;
private:
};