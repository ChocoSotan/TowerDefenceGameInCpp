#pragma once
#include"Enemy.h"
#include"DxLib.h"
//�ő�l���R���X�g���N�^�Őݒ�B
//�\������ꏊ�ƌĂяo�����_�ł̐��l�������Ƃ��Ď󂯎��B
class Gauge {
public:
	Gauge(double maxnumber) {
		this->maxnumber = maxnumber;
	}
	virtual~Gauge(){}
	//�\���ʒu���ω�����Q�[�W
	virtual void drawFloatingGauge(Vector2D position, double currentnumber)const { return; };
	//�\���ʒu���Œ肳��Ă���Q�[�W
	virtual void drawImmovableGauge(double currentnumber)const { return; };
	void drawTimeGauge(){}
protected:
	double maxnumber;
};
//�G�l�~�[�̗͎̑c�ʂȂ�
class HPGauge :public Gauge {
public:
	HPGauge(double maxnumber):Gauge(maxnumber){}
	void drawFloatingGauge(Vector2D position, double currentnumber)const override;
};
//�E�F�[�u�̎c�莞�ԗp
class TimeGauge :public Gauge {
public:
	TimeGauge(double maxnumber) :Gauge(maxnumber){}
	void setMaxNumber(double maxnumber) { this->maxnumber = maxnumber; }
	void drawImmovableGauge(double currentnumber)const override;
};
//�����̎c�ʗp
class MoneyGauge :public Gauge {
	MoneyGauge(double maxnumber):Gauge(maxnumber){}
	void setMaxNumber(double maxnumber) { this->maxnumber = maxnumber; }
	void drawImmovableGauge(double currentnumber)const override;
};