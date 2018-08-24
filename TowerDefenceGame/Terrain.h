#pragma once

#include "Vector2D.h"
#include "Texture.h"

#include <string>

/// <summary>
/// Terrain(map) class.
/// </summary>
class TerrainBase {
public:
	TerrainBase(bool canplaceturret, Vector2D pos) {
		this->canplaceturret = canplaceturret;
		this->position = pos;
		this->texture = texture;
	}
	virtual ~TerrainBase() {}

	bool canPlaceTurret() { return canplaceturret; }
	bool init(Texture *texture, std::string filename);
	void draw();

protected:
	bool canplaceturret;
	Vector2D position;
	Texture *texture;
	std::string filename;
};

class BasicTerrain : public TerrainBase {
public:
	BasicTerrain(bool canplaceturret, Vector2D pos) : TerrainBase(canplaceturret, pos) { }
	~BasicTerrain() {}


private:
	// MAY : add StatusBonus for placed turret
};