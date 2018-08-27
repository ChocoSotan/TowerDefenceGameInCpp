#pragma once

#include "Enemy.h"
#include "Terrain.h"
#include "Turret.h"
#include "Wave.h"
#include "WaveSystem.h"
#include "Texture.h"
#include "Button.h"


#include <string>
#include <sstream>
#include <vector>
#include <fstream>


class Loader {
public:
	Loader() {}
	virtual ~Loader() {}

protected:
	// split string by delimiter and store to container
	void splitString(const std::string &line, std::vector<std::string> &container, const char delim = ',');
	
	
};




class FieldLoader : public Loader {
public:
	FieldLoader() {}
	~FieldLoader() {}

	bool load(std::string filename, std::vector<std::vector<TerrainBase*>> &vec, const Vector2D &pos, const int size);
	bool initField(std::string filename_texture, std::string filename_id, std::vector<std::vector<TerrainBase*>> &vec, Texture *texture);
};

class PathLoader : public Loader {
public:
	PathLoader() {}
	~PathLoader() {}

	bool load(std::string filename, std::vector<Vector2D> &vpath);
};

class TurretLoader : public Loader {
public:
	TurretLoader() {}
	~TurretLoader() {}

	bool load(std::string filename, std::vector<TurretBase*> &vec);
};

class WaveLoader : public Loader {
public:
	WaveLoader() {}
	~WaveLoader() {}

	bool load(std::string filename, std::vector<Wave*> &vec, Vector2D &pos);
};

class TextureLoader : public Loader {
public:
	TextureLoader() {}
	~TextureLoader() {}

	bool load(std::string filename, Texture *texture);
};

class ButtonLoader : public Loader {
public:
	ButtonLoader() {}
	~ButtonLoader() {}

	bool load(std::string filename, std::vector<Button*> &vbutton, Texture *texture);
};
