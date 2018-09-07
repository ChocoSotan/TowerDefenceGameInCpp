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
#define Blue GetColor(0,0,255)
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
	// void constructTurret();



private:
	Mouse mouse;

	std::vector<TurretBase*> vturret;
	std::vector<TurretBase*> vturret_ini;		// to copy to vturret
	std::vector<EnemyBase*> venemy;
	std::vector<Wave*> vwave;
	std::vector<Vector2D> vpath;
	std::vector<std::vector<TerrainBase*>> vterrain;
	
	WaveSystem *ws = new WaveSystem(&this->venemy, 300, &this->texture);
	Texture texture;

	std::vector<Button*> vbutton;
	std::vector<ToggleButton*> vtbutton;

	// option flags
	bool isPaused;
	int ffmul;

	// in game numeric
	long long resource;
	int health;
};

Game::Game(ISceneChanger *changer) : BaseScene(changer) {
	this->isPaused = false;
	this->ffmul = 1;
	resource = 100;			// initial resource
	health = 20;			// initial health
}

void Game::Initialize() {
	// Loading Path
	PathLoader pl = PathLoader();
	_RPT0(_CRT_WARN, "Path initializing...\t");
	pl.load("data\\stage\\01\\path.csv", this->vpath) ? _RPT0(_CRT_WARN, "Success!\n") : _RPT0(_CRT_WARN, "Failed...\n");

	// Loading Turrets
	TurretLoader tul = TurretLoader();
	_RPT0(_CRT_WARN,"Turret initializing...\t");
	tul.load("data\\turret\\turret.csv", this->vturret_ini) ? _RPT0(_CRT_WARN, "Success!\n") : _RPT0(_CRT_WARN, "Failed...\n");
	for (auto i = vturret_ini.begin(); i != vturret_ini.end(); i++) {
		(*i)->changePriority(new ClosestBase(this->vpath));
	}

	// Loading Textures
	TextureLoader tel = TextureLoader();
	_RPT0(_CRT_WARN, "Texture initializing...\t");
	tel.load("data\\texturelist.csv", &this->texture) ? _RPT0(_CRT_WARN, "Success!\n") : _RPT0(_CRT_WARN, "Failed...\n");

	// Loading WaveData
	ws->init("data\\stage\\01\\wave.csv", vpath[0]);

	// Loading ButtonData
	ButtonLoader bl = ButtonLoader();
	_RPT0(_CRT_WARN, "Button initializing...\t");
	bl.load("data\\buttonlist.csv", this->vbutton, this->vtbutton, &this->texture) ? _RPT0(_CRT_WARN, "Success!\n") : _RPT0(_CRT_WARN, "Failed...\n");

	// Loading Field
	FieldLoader fl = FieldLoader();
	_RPT0(_CRT_WARN, "Field initializing(canplace flag)...\t");
	fl.load("data\\stage\\01\\map_canplace.csv", this->vterrain, Vector2D(80, 56), 64) ? _RPT0(_CRT_WARN, "Success!\n") : _RPT0(_CRT_WARN, "Failed...\n");
	_RPT0(_CRT_WARN, "Field initializing...(set texture)\t");
	fl.initField("data\\stage\\01\\map_texture.csv", "data\\stage\\01\\map_textureid.csv", this->vterrain, &this->texture) ? _RPT0(_CRT_WARN, "Success!\n") : _RPT0(_CRT_WARN, "Failed...\n");

	for (auto i = vturret_ini.begin(); i != vturret_ini.end(); i++) {
		_RPTN(_CRT_WARN, "Name:%s\tDmg:%.1f\tRate:%.1f\tRange:%.1f\n", (*i)->getName().c_str(), (*i)->getDamage(), (*i)->getFireRate(), (*i)->getRange());
	}
}

void Game::Update() {
	/* Mouse */
	this->mouse.update();

	/* Button */
	// button update
	for (auto i = vbutton.begin(); i != vbutton.end(); i++) { (*i)->update(this->mouse); }
	for (auto i = vtbutton.begin(); i != vtbutton.end(); i++) { (*i)->update(); }
	
	// toggle pause
	if (vbutton[0]->isClicked()) { isPaused = isPaused? false : true; }

	// toggle fast forward
	if (vbutton[1]->isClicked()) { ffmul = ffmul == 1 ? 2 : 1; }

	// next wave
	if (vbutton[2]->isClicked()) { ws->nextWave(); }

	// construct turret
	{
		int selectedturret = vtbutton[0]->getChannel();
		if (selectedturret != -1) {
			for (int i = 12; i < 133; i++) {
				if (!(vbutton[i]->isClicked()))continue;
				if (!vterrain[(int)floor((i - 12) / 11)][(i - 12) % 11]->canPlaceTurret())break;

				// construction
				if (!vturret_ini[selectedturret]->canConstruct(this->resource)) {
					vtbutton[0]->clearChannel();
					break;
				}
				this->resource -= vturret_ini[selectedturret]->getConstructCost();
				vturret.push_back(vturret_ini[selectedturret]);

				vturret[(signed)vturret.size()]->setPosition(Vector2D(vbutton[i]->getPosition().getX() + 32, vbutton[i]->getPosition().getY() + 32));
				vterrain[(int)floor((i - 12) / 11)][(i - 12) % 11]->changeCanPlaceTurret();
				vtbutton[0]->clearChannel();
			}
		}
		else {
			for (int i = 12; i < 133; i++) {
				if (!(vbutton[i]->isClicked()))continue;
				if (vterrain[(int)floor((i - 12) / 11)][(i - 12) % 11]->canPlaceTurret())break;

				// upgrade

			}
		}
	}

	// for debug
	for (int i = 0; i < (signed)vbutton.size(); i++) {
		if (vbutton[i]->isClicked()) {
			_RPT1(_CRT_WARN, "BUTTON %d WAS CLICKED.\n", i);
		}
	}
	/* Not Paused */
	if (isPaused) return;

	for (int i = 0; i < ffmul; i++) {
		ws->update(this->venemy);
	}

	for (auto i = venemy.begin(); i != venemy.end(); i++) {
		if (!(*i)->isAlive())continue;
		for (int j = 0; j < ffmul; j++) {
			(*i)->update(vpath);
		}
	}
	for (auto i = vturret.begin(); i != vturret.end(); i++) {
		for (int j = 0; j < ffmul; j++) {
			(*i)->attack(&venemy);
		}
	}


	

}

void Game::Draw() {
	DrawFormatString(0, 0, GetColor(255, 255, 255), "ƒQ[ƒ€");


	// button
	for (auto i = vbutton.begin(); i != vbutton.end(); i++) {
		(*i)->draw();
	}

	// terrain
	for (int i = 0; i < (signed)vterrain.size(); i++) {
		for (int j = 0; j < (signed)vterrain[i].size(); j++) {
			vterrain[j][i]->draw();
		}
	}

	// WaveGuage
	DrawString(8, 56, "Wave", White);
	// ws->draw(Vector2D(8,56), "", "", 8);
	DrawBox(8, 56, 72, 768 - 8, White, FALSE);

	// Money
	DrawString(208, 8, "Money", White);
	DrawBox(208, 8, 528, 48, White, FALSE);
	DrawFormatString(208, 28, White, "%d", this->resource);

	// Health
	DrawString(536, 8, "Health", White);
	DrawBox(536, 8, 656, 48, White, FALSE);
	DrawFormatString(536, 28, White, "%d", this->health);

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

	for (auto i = vturret.begin(); i != vturret.end(); i++) {
		(*i)->draw(this->texture);
	}

	// info
	DrawString(160 + 10 * Boxsize, 340, "Information", White);
	DrawBox(160 + 10 * Boxsize, 340, 1024 - 16, 768 - 16, White, FALSE);

	for (auto i = venemy.begin(); i != venemy.end(); i++) {
		if (!(*i)->isAlive())continue;
		(*i)->draw(this->texture);
	}

	for (int i = 0; i < (signed)venemy.size(); i++) {
		DrawFormatString(200, 0 + i*20, White, "HP:%f", venemy[i]->getHitpoint());
	}

	// turret selection
	DrawFormatString(0, 100, White, "%d", vtbutton[0]->getChannel());
	
	// wavecount
	DrawFormatString(0, 140, White, "wavecount:%d", (int)ws->getCount());

}

void Game::Finalize() {
	for (auto i = vbutton.begin(); i != vbutton.end(); i++) {
		delete (*i);
	}
	for (auto i = vtbutton.begin(); i != vtbutton.end(); i++) {
		delete (*i);
	}
	for (auto i = vturret.begin(); i != vturret.end(); i++) {
		// delete (*i);
	}
	for (int i = 0; i < (signed)vterrain.size(); i++) {
		for (int j = 0; j < (signed)vterrain[i].size(); j++) {
			delete vterrain[j][i];
		}
	}
	texture.deleteHandleAll();
}