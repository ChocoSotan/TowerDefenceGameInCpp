#include "Terrain.h"

#include "DxLib.h"



void TerrainBase::draw(int handle) {
	DrawGraph((int)position.getX(), (int)position.getY(), handle, FALSE);
}


