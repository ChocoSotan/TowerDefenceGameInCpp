#pragma once
#include"Enemy.h"
#include"DxLib.h"
//最大値をコンストラクタで設定。
//表示する場所と呼び出し時点での数値を引数として受け取る。
class Gauge {
public:
	Gauge(double maxnumber) {
		this->maxnumber = maxnumber;
	}
	virtual~Gauge(){}
	//表示位置が変化するゲージ
	virtual void drawFloatingGauge(Vector2D position, double currentnumber)const { return; };
	//表示位置が固定されているゲージ
	virtual void drawImmovableGauge(double currentnumber)const { return; };
	void drawTimeGauge(){}
protected:
	double maxnumber;
};
//エネミーの体力残量など
class HPGauge :public Gauge {
public:
	HPGauge(double maxnumber):Gauge(maxnumber){}
	void drawFloatingGauge(Vector2D position, double currentnumber)const override;
};
//ウェーブの残り時間用
class TimeGauge :public Gauge {
public:
	TimeGauge(double maxnumber) :Gauge(maxnumber){}
	void setMaxNumber(double maxnumber) { this->maxnumber = maxnumber; }
	void drawImmovableGauge(double currentnumber)const override;
};
//資金の残量用
class MoneyGauge :public Gauge {
	MoneyGauge(double maxnumber):Gauge(maxnumber){}
	void setMaxNumber(double maxnumber) { this->maxnumber = maxnumber; }
	void drawImmovableGauge(double currentnumber)const override;
};