#pragma once

#include "Vector2D.h"

class Turret {
public:
	Turret() {}
	virtual ~Turret() {}

	virtual void attack();

private:
	double attackpower;		// �U����
	double firerate;		// �U�����x
	double attackrange;		// �U���͈�

	Vector2D position;		// ��ʏ�̈ʒu
};