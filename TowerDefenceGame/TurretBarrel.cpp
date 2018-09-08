#include "TurretBarrel.h"

#include "DxLib.h"
#include "Texture.h"
#include "Vector2D.h"

void TurretBarrel::draw(const Texture &texture, std::string filename) const {
	DrawRotaGraph(pos.getX(), pos.getY(), 1.0, angle, texture.getHandle(filename), TRUE);
}
