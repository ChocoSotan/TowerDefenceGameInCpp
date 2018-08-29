#pragma once
#include"Enemy.h"
//maxhitpointをエネミーが持てばここの内容も変わる。
//エネミーがこれを持つことを想定。
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