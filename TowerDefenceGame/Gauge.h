#pragma once
#include"Enemy.h"
#include"DxLib.h"
//�ő�l���R���X�g���N�^�Őݒ�B
//�\������ꏊ�ƌĂяo�����_�ł̐��l�������Ƃ��Ď󂯎��B
class Gauge {
public:
	Gauge(int sixe_x,int size_y,const int &surfacecolor,const int &backcolor,int difference_x,int difference_y) {
		this->size_x = size_x;
		this->size_y = size_y;
		this->surfacecolor = surfacecolor;
		this->backcolor = backcolor;
		this->difference_x = difference_x;
		this->difference_y = difference_y;
	}
	Gauge(int size_x, int size_y, const int &surfacecolor, const int &baclcor) {
		this->size_x = size_x;
		this->size_y = size_y;
		this->surfacecolor = surfacecolor;
		this->backcolor = backcolor;
		this->difference_x = 0;
		this->difference_y = 0;
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