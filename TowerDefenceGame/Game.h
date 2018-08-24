#pragma once

#include "Scene.h"
#include "DxLib.h"

#include "Enemy.h"
#include "Turret.h"
#include "Terrain.h"

#include "Texture.h"
#include "Button.h"
#include "Mouse.h"
#include "Loader.h"
#include "ToggleButton.h"

#include <vector>

#include "TargetPriority.h"

// for DxLib's Color Code
#define White GetColor(255,255,255)
#define Black GetColor(0,0,0)
#define Red GetColor(255,0,0)
#define Green GetColor(0,255,0)
#define Blue Getcolor(0,0,255)
#define Yellow GetColor(255,255,0)
#define SkyBlue GetColor(0,255,255)
#define Purple GetColor(255,0,255)


class Game : public BaseScene {
public:
	Game(ISceneChanger *changer);
	~Game() {}

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Finalize() override;

private:
	Mouse mouse;

	std::vector<TurretBase*> vturret;
	std::vector<TurretBase*> vturret_ini;		// to copy to vturret
	std::vector<EnemyBase*> venemy;
	std::vector<Wave*> vwave;
	std::vector<Vector2D> vpath;
	std::vector<std::vector<TerrainBase*>> vterrain;
	
	WaveSystem *ws;
	Texture texture;

	std::vector<Button*> button;
	ToggleButton tbutton;

	bool isPaused;
	bool isFFed;
};

Game::Game(ISceneChanger *changer) : BaseScene(changer) {
	this->isPaused = false;
	this->isFFed = false;
}

void Game::Initialize() {
	// Loading Path
	PathLoader pl = PathLoader();
	pl.load("data\\stage\\01\\path.csv", this->vpath);

	// Loading Turret
	TurretLoader tl = TurretLoader();
	tl.load("data\\turret\\turret.csv", this->vturret_ini);

	// Loading WaveData
	ws = new WaveSystem(&this->venemy, 300);
	ws->init("data\\stage\\01\\wave.csv", vpath[0]);




	/* Pooling to Texture Pool */
	texture.pool("texture/Game/Buttons/Stop.png");
	texture.pool("texture/Game/Buttons/Start.png");
	texture.pool("texture/Game/Buttons/NotFastForward.png");
	texture.pool("texture/Game/Buttons/FastForward.png");
	texture.pool("texture/Game/Buttons/NextWave.png");
	texture.pool("texture/Game/Turrets/TurretBases/default.png");
	texture.pool("texture/Game/Turrets/TurretBases/default(selected).png");

	// Start/Stop Button
	std::vector<std::string> vfilename;
	vfilename.push_back("texture/Game/Buttons/Stop.png");
	vfilename.push_back("texture/Game/Buttons/Start.png");
	button.push_back(new Button(8, 8));
	button[0]->init(&texture, vfilename);

	// FastForward Button
	vfilename.clear();
	vfilename.push_back("texture/Game/Buttons/NotFastForward.png");
	vfilename.push_back("texture/Game/Buttons/FastForward.png");
	button.push_back(new Button(56, 8));
	button[1]->init(&texture, vfilename);

	// NextWave Button
	button.push_back(new Button(104, 8));
	button[2]->init(&texture, std::string("texture/Game/Buttons/NextWave.png"));

	// Buying Turret Button(Toggle)
	vfilename.clear();
	vfilename.push_back("texture/Game/Turrets/TurretBases/default.png");
	vfilename.push_back("texture/Game/Turrets/TurretBases/default(selected).png");
	for (int i = 0; i < 3; i++)for (int j = 0; j < 3; j++) {
		Button *turretbutton = new Button(808 + j * 64, 132 + i * 64);
		button.push_back(turretbutton);
		tbutton.addButton(turretbutton);
	}
	for(int i = 0;i<9;i++)button[3 + i]->init(&texture, vfilename);

	// for debug
	vturret.push_back(vturret_ini[0]);
	vturret[0]->changePriority(new ClosestTurret(this->vpath));

#ifdef _DEBUG
	for (int i = 0; i < vturret_ini.size(); i++) {
		printfDx("Name:%s\tDmg:%.1f\tRate:%.1f\n", vturret_ini[i]->getName().c_str(), vturret_ini[i]->getDamage(), vturret_ini[i]->getFireRate());
	}
#endif // _DEBUG
}

void Game::Update() {
	/* Mouse */
	this->mouse.update();

	/* Button */
	// button update
	for (auto i = button.begin(); i != button.end(); i++) {
		(*i)->update(this->mouse);
	}
	tbutton.update();

	// toggle pause
	if (button[0]->isClicked()) {
		isPaused = isPaused? false : true;
	}

	// toggle fast forward
	if (button[1]->isClicked()) {
		isFFed = isFFed? false : true;
	}

	// next wave
	if (button[2]->isClicked()) {
		ws->nextWave();
	}
	
	
	if (isPaused) return;

	/* Not Paused */

	ws->update(this->venemy);
	if(isFFed)ws->update(this->venemy);

	for (auto i = venemy.begin(); i != venemy.end(); i++) {
		(*i)->move(vpath);
		if (isFFed) {
			(*i)->move(vpath);
		}
	}
	for (auto i = vturret.begin(); i != vturret.end(); i++) {
		(*i)->attack(venemy);
		if (isFFed) {
			(*i)->attack(venemy);
		}
	}


}

void Game::Draw() {
	DrawFormatString(0, 0, GetColor(255, 255, 255), "ƒQ[ƒ€");

	for (auto i = button.begin(); i != button.end(); i++) {
		(*i)->draw();
	}

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

	// Options
	DrawString(976, 8, "Opt", White);
	DrawBox(976, 8, 1016, 48, White, FALSE);


	// field
	DrawString(80, 56, "Field", White);
	const int Boxsize = 64;
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 11; j++) {
			DrawBox(80 + j * Boxsize, 56 + i * Boxsize, 144 + j * Boxsize, 120 + i * Boxsize, White, FALSE);
		}
	}

	// turret construction/information menu
	DrawBox(152 + 10 * Boxsize, 56, 1024 - 8, 768 - 8, White, FALSE);
	DrawBox(160 + 10 * Boxsize, 64, 1024 - 16, 348 - 16, White, FALSE);

	// turrets
	DrawString(160 + 10 * Boxsize, 64, "Turret", White);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			DrawBox(168 + 10 * Boxsize + j * 64, 132 + i * 64, 232 + 10 * Boxsize + j * 64, 196 + i * 64, White, FALSE);
		}
	}

	// info
	DrawString(160 + 10 * Boxsize, 340, "Information", White);
	DrawBox(160 + 10 * Boxsize, 340, 1024 - 16, 768 - 16, White, FALSE);

	for (int i = 0; i < venemy.size(); i++) {
		DrawCircle((int)venemy[i]->getPosition().getX(), (int)venemy[i]->getPosition().getY(), 4, White);
	}
	for (int i = 0; i < venemy.size(); i++) {
		DrawFormatString(0, 220 + i*20, White, "venemy[%d].hitpoint:%f", i, venemy[i]->getHitpoint());
	}
	DrawFormatString(0, 140, White, "wavecount:%d", (int)ws->getCount());
	DrawFormatString(0, 160, White, "vturret[0].firerate:%f", vturret[0]->getFireRate());
	DrawFormatString(0, 180, White, "vturret[0].wait:%f", vturret[0]->getWaitTime());
}

void Game::Finalize() {
	for (auto i = button.begin(); i != button.end(); i++) {
		delete (*i);
	}
}