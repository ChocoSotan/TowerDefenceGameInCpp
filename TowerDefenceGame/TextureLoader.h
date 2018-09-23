#pragma once

#include "Loader.h"
class Texture;

#include <string>

class TextureLoader : public Loader {
public:
	TextureLoader() {}
	~TextureLoader() {}

	bool load(std::string filename, Texture *texture);
};