#pragma once

#include "Scene.h"
#include "DxLib.h"

#include "Enemy.h"
#include "Turret.h"
#include "Terrain.h"

#include "Texture.h"

#include <vector>

#define White GetColor(255,255,255)

class Game : public BaseScene {
public:
	Game(ISceneChanger *changer);
	~Game() {}

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Finalize() override;

private:
	std::vector<TurretBase*> vturret;
	std::vector<EnemyBase*> venemy;
	std::vector<Vector2D> vpath;
	std::vector<std::vector<TerrainBase*>> vterrain;
	
	Texture *texture;

};

Game::Game(ISceneChanger *changer) : BaseScene(changer) {

}

void Game::Initialize() {
	// for debug
	NormalEnemy *normalenemy = new NormalEnemy(20,4,2,10);
	Vector2D *vec = new Vector2D(0, 364);
	venemy.push_back(normalenemy);
	venemy[0]->setPosition(*vec);
	vpath.push_back(*vec);
	vec = new Vector2D(32*3, 364);
	vpath.push_back(*vec);
	vec = new Vector2D(32*3, 268);
	vpath.push_back(*vec);
	vec = new Vector2D(32*8, 268);
	vpath.push_back(*vec);
	vec = new Vector2D(32 * 8, 460);
	vpath.push_back(*vec);
}

void Game::Update() {
	venemy[0]->move(vpath);
}

void Game::Draw() {
	DrawFormatString(0, 0, GetColor(255, 255, 255), "�Q�[��");

	
	// Stop/Start
	DrawString(8, 8, "S/S", White);
	DrawBox(8, 8, 48, 48, White, FALSE);
	
	// FastForward
	DrawString(56, 8, "FF", White);
	DrawBox(56, 8, 96, 48, White, FALSE);

	// NextWave
	DrawString(104, 8, "NW", White);
	DrawBox(104, 8, 144, 48, White, FALSE);

	// WaveGuage
	DrawString(8, 56, "Wave", White);
	DrawBox(8, 56, 72, 768 - 8, White, FALSE);

	// Money
	DrawString(208, 8, "Money", White);
	DrawBox(208, 8, 528, 48, White, FALSE);

	// Health
	DrawString(536, 8, "Health", White);
	DrawBox(536, 8, 656, 48, White, FALSE);


	// field
	DrawString(80, 56, "Field", White);
	const int Boxsize = 64;
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 11; j++) {
			DrawBox(80 + j * Boxsize, 56 + i * Boxsize, 144 + j * Boxsize, 120 + i * Boxsize, White, FALSE);
		}
	}

	// construction/information menu
	DrawBox(152 + 10 * Boxsize, 56, 1024 - 8, 768 - 8, White, FALSE);
	DrawBox(160 + 10 * Boxsize, 64, 1024 - 16, 332, White, FALSE);

	// turrets
	DrawString(160 + 10 * Boxsize, 64, "Turret", White);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			DrawBox(168 + 10 * Boxsize + j * 64, 132 + i * 64, 232 + 10 * Boxsize + j * 64, 196 + i * 64, White, FALSE);
		}
	}

	DrawString(160 + 10 * Boxsize, 340, "Information", White);
	DrawBox(160 + 10 * Boxsize, 340, 1024 - 16, 768 - 16, White, FALSE);
}

void Game::Finalize() {

}