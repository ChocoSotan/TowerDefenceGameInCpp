#include"TurretBarrel.h"

void TurretBarrel::draw(int x,int y,Texture *texture) {
	DrawRotaGraph(x, y, 1, this->angle, texture->getHandle("texture/Game/Turrets/TurretBarrel"), TRUE, FALSE);
}