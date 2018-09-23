#include "Gauge.h"

#include "Vector2D.h"
#include "DxLib.h"

void Gauge::update(double num_max, double num_now) {
	this->percentage = (int)(num_now / num_max * 100);
}
void Gauge::draw(const Vector2D &position) const {
	//DrawBox((int)position.getX(), position.getY(), position.getX() + this->size_x, position.getY() + this->size_y, this->backcolor, TRUE);

	//DrawBox(position.getX(), position.getY(), position.getX() + (this->size_x * this->percentage) / 100, position.getY() + this->size_y, this->surfacecolor, TRUE);
}