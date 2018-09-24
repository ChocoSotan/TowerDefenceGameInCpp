#pragma once

#include "Loader.h"
class Vector2D;

#include <string>
#include <vector>

class PathLoader : public Loader {
public:
	PathLoader() {}
	~PathLoader() {}

	bool load(const std::string &filename, std::vector<Vector2D> &vpath);
};