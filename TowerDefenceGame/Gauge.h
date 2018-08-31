#pragma once
#include"Enemy.h"
#include"DxLib.h"
//最大値をコンストラクタで設定。
//表示する場所と呼び出し時点での数値を引数として受け取る。
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
	//二数を比較してpercentageを更新。
	void update(double num_max, double num_now);
	//表示位置が変化するゲージ
	void drawGauge(const Vector2D &position)const;
protected:
	int percentage;
	int size_x,size_y;
	int surfacecolor;
	int backcolor;
	int difference_x;
	int difference_y;
};