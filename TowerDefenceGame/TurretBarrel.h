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

	void draw(const Texture &texture, const std::string path) const;
	void update(double angle, const Vector2D &pos) {
		this->angle = angle;
		this->pos = pos;
	}
	void setPosition(const Vector2D &pos) { this->pos = pos; };

private:
	Vector2D pos;
	double angle;
};