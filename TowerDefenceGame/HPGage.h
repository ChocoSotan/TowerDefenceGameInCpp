#pragma once
#include"Enemy.h"
//エネミーが各自持っていることを想定。
//敵の最大HPと現状HPが必要。
class HPGage {
public:
	HPGage() {

	}
	~HPGage(){}
	void draw(Vector2D,double maxhitpoint,double hitpoint)const;
private:
};