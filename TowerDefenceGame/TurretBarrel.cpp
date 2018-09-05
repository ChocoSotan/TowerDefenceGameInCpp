#include"TurretBarrel.h"

void TurretBarrel::draw(int x,int y,int handle) {
	DrawRotaGraph(x, y, 1, this->angle,handle, TRUE, FALSE);
}