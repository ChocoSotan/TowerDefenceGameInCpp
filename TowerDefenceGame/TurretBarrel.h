#pragma once

#include "DxLib.h"
#include "Vector2D.h"
#include "Texture.h"

#include <math.h>

class TurretBarrel {
public:
	TurretBarrel() {
		this->angle = 0;
	}
	~TurretBarrel() {}

	void draw(const Texture &texture, std::string filename) const;
	void update(double angle, const Vector2D &pos) {
		this->angle = angle;
		this->pos = pos;
	}

private:
	Vector2D pos;
	double angle;
};