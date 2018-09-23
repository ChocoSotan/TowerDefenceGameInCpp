#pragma once

#include "Loader.h"

class Vector2D;
class Wave;

#include <string>
#include <vector>

class WaveLoader : public Loader {
public:
	WaveLoader() {}
	~WaveLoader() {}

	bool load(std::string filename, std::vector<Wave*> &vec, const Vector2D &pos);
};