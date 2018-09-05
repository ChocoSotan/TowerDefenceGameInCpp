#pragma once
#include<math.h>
#include "DxLib.h"
#include "Vector2D.h"
#include "Texture.h"

class TurretBarrel {
public:
	TurretBarrel() {
		this->angle =atan2(-1.0,-1.0);
	}
	~TurretBarrel() {
		
	}
	void draw(int x, int y,int handle);
	double getAngle() { return this->angle; }
	void setAngle(double angle) { this->angle = angle; }

private:
	double angle;
};