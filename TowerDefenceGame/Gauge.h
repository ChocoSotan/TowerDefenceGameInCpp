#pragma once

#include "Vector2D.h"

class Gauge {
public:
	Gauge(int size_x,int size_y,const int &surfacecolor,const int &backcolor) {
		this->size_x = size_x;
		this->size_y = size_y;
		this->surfacecolor = surfacecolor;
		this->backcolor = backcolor;

	}
	virtual~Gauge(){}

	void update(double num_max, double num_now);
	void draw(const Vector2D &position)const;

protected:
	int percentage;
	int size_x,size_y;
	int surfacecolor;
	int backcolor;
};