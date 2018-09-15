#pragma once

#include "Loader.h"

#include "Sound.h"

#include <string>
#include <vector>
#include <fstream>

class SoundLoader : public Loader {
public:
	SoundLoader() {}
	~SoundLoader() {}

	bool load(const std::string &filename, Sound *sound);


private:


};

