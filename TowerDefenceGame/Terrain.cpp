#include "Terrain.h"

#include "DxLib.h"


bool TerrainBase::init(Texture *texture, std::string filename) {
	if(!texture->pool(filename))return false;
	return true;
}


void TerrainBase::draw() {
	DrawGraph((int)position.getX(), (int)position.getY(), texture->getHandle(), FALSE);
}


