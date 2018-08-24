#include "Terrain.h"

#include "DxLib.h"


bool TerrainBase::init(Texture *texture, std::string filename) {
	this->texture = texture;
	this->filename = filename;
	return true;
}


void TerrainBase::draw() {
	DrawGraph((int)position.getX(), (int)position.getY(), texture->getHandle(filename), FALSE);
}


