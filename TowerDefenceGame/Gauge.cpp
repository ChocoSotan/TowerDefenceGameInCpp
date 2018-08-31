#include"Gauge.h"

void Gauge::update(double num_max, double num_now) {
	this->percentage = (int)(num_now / num_max * 100);
}
void Gauge::drawGauge(const Vector2D &position)const {
	DrawBox(position.getX()+difference_x, position.getY()+difference_y, position.getX()+size_x+ difference_x, position.getY()+size_y+difference_y,GetColor(255,0,0),TRUE);
	DrawBox(position.getX()+difference_x, position.getY()+difference_y, position.getX()+(size_x*percentage)/100+difference_x, position.getY()+size_y+difference_y, GetColor(0, 255, 0), TRUE);
}