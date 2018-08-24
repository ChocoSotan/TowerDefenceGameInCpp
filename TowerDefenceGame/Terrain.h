#pragma once

#include "Vector2D.h"

/// <summary>
/// Terrain(map) class.
/// </summary>
class TerrainBase {
public:
	TerrainBase(bool canplaceturret, Vector2D &pos) {
		this->canplaceturret = canplaceturret;
		this->position = pos;
	}
	virtual ~TerrainBase() {}

	bool canPlaceTurret() { return canplaceturret; }
	void draw(int handle);

protected:
	bool canplaceturret;
	Vector2D position;
};

class BasicTerrain : public TerrainBase {
public:
	BasicTerrain(bool canplaceturret, Vector2D &pos) : TerrainBase(canplaceturret, pos) { }
	~BasicTerrain() {}


private:
	// MAY : add StatusBonus for placed turret
};