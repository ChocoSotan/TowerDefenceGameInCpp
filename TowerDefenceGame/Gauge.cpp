#include"Gauge.h"

void Gauge::update(double num_max, double num_now) {
	this->percentage = (int)(num_now / num_max * 100);
}
void Gauge::drawGauge(const Vector2D &position)const {
	DrawBox(position.getX()+this->difference_x, position.getY()+this->difference_y, position.getX()+this->size_x+ this->difference_x, position.getY()+this->size_y+this->difference_y,this->backcolor,TRUE);
	DrawBox(position.getX()+this->difference_x, position.getY()+this->difference_y, position.getX()+(this->size_x*this->percentage)/100+this->difference_x, position.getY()+this->size_y+this->difference_y,this->surfacecolor, TRUE);
}