#pragma once

#include "Loader.h"
class TerrainBase;
class Vector2D;
class Texture;

#include <string>
#include <vector>

class FieldLoader : public Loader {
public:
	FieldLoader() {}
	~FieldLoader() {}

	bool load(std::string filename, std::vector<std::vector<TerrainBase*>> &vec, const Vector2D &pos, const int size);
	bool initField(std::string filename_texture, std::string filename_id, std::vector<std::vector<TerrainBase*>> &vec, Texture *texture);
};