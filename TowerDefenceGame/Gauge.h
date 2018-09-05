#pragma once
#include"Enemy.h"
#include"DxLib.h"
class Gauge {
public:
	Gauge(int size_x,int size_y,const int &surfacecolor,const int &backcolor,int difference_x=0,int difference_y=0) {
		this->size_x = size_x;
		this->size_y = size_y;
		this->surfacecolor = surfacecolor;
		this->backcolor = backcolor;
		this->difference_x = difference_x;
		this->difference_y = difference_y;
	}
	virtual~Gauge(){}
	//�񐔂��r����percentage���X�V�B
	void update(double num_max, double num_now);
	//�\���ʒu���ω�����Q�[�W
	void drawGauge(const Vector2D &position)const;
protected:
	int percentage;
	int size_x,size_y;
	int surfacecolor;
	int backcolor;
	int difference_x;
	int difference_y;
};