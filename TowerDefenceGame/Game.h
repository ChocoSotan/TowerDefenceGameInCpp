#pragma once

#pragma warning(disable:4996)

// Systems
#include "Scene.h"
#include "ISceneChanger.h"
#include "DxLib.h"

#include "Enemy.h"
#include "Turret.h"
#include "Terrain.h"
#include "Texture.h"
#include "Button.h"
#include "ToggleButton.h"
#include "TurretFactory.h"
#include "InformationWindow.h"
#include "Sound.h"
#include "Wave.h"
#include "WaveSystem.h"

#include "Keyboard.h"
#include "Mouse.h"

// Loaders
#include "Loader.h"
#include "FieldLoader.h"
#include "PathLoader.h"
#include "SoundLoader.h"
#include "ButtonLoader.h"
#include "TextureLoader.h"

// Debugger
#include "Debugger.h"

#include <vector>
#include <string>
#include <iomanip>
#include <sstream>

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
	Game(ISceneChanger *changer, const int stage);
	~Game() {}

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Finalize() override;

private:
	// void constructTurret();



private:
	Debugger dbg;
	Keyboard keyboard;
	Mouse mouse;

	std::vector<TurretBase*> vturret;
	std::vector<const TurretBase*> vturret_ini;		// to copy to vturret
	std::vector<EnemyBase*> venemy;
	std::vector<Wave*> vwave;
	std::vector<Vector2D> vpath;
	std::vector<std::vector<TerrainBase*>> vterrain;
	
	WaveSystem *ws = new WaveSystem(300);
	TurretFactory *tf = new TurretFactory();
	Texture texture;
	Sound sound;
	InformationWindow info;

	std::vector<Button*> vbutton;
	std::vector<ToggleButton*> vtbutton;

	// stage no
	int stage;

	// option flags
	bool isPaused;
	int ffmul;

	// in game numeric
	long long resource;
	int health;


private:
	// fonts
	std::vector<int> fonthandle;

};

Game::Game(ISceneChanger *changer, const int stage) : BaseScene(changer) {
	this->stage = stage;
	this->isPaused = true;
	this->ffmul = 1;
	resource = 100;			// initial resource
	health = 20;			// initial health

}

void Game::Initialize() {

	// Loading Path
	PathLoader pl = PathLoader();
	dbg.print("Initializing Pathes......");
	std::stringstream ss;
	ss << "data\\stage\\" << std::setfill('0') << std::setw(2) << std::right << this->stage << "\\path.csv";
	pl.load(ss.str(), this->vpath) ? dbg.print("Success!") : dbg.print("Failed...");

	// Loading Turrets
	dbg.print("Initializing Turrets......");
	tf->load("data\\turret\\turret.csv", this->vpath) ? dbg.print("Success!") : dbg.print("Failed...");
	this->vturret_ini = tf->getDataAll();

	// Loading Textures
	TextureLoader tel = TextureLoader();
	dbg.print("Initializing Textures......");
	tel.load("data\\texturelist.csv", &this->texture) ? dbg.print("Success!") : dbg.print("Failed...");

	// Loading Sounds
	SoundLoader sl = SoundLoader();
	dbg.print("Initializing Sounds......");
	sl.load("data\\soundlist.csv", &this->sound) ? dbg.print("Success!") : dbg.print("Failed...");

	// Loading WaveData
	ws->init("data\\stage\\01\\wave.csv", vpath[0]);

	// Loading ButtonData
	ButtonLoader bl = ButtonLoader();
	dbg.print("Initializing Buttons.....");
	bl.load("data\\buttonlist.csv", this->vbutton, this->vtbutton, &this->texture) ? dbg.print("Success!") : dbg.print("Failed...");

	// Loading Field
	FieldLoader fl = FieldLoader();
	dbg.print("Initializing Fields(Place)......");
	fl.load("data\\stage\\01\\map_canplace.csv", this->vterrain, Vector2D(80, 56), 64) ? dbg.print("Success!") : dbg.print("Failed...");
	dbg.print("Initializing Fields(Set textures)......");
	fl.initField("data\\stage\\01\\map_texture.csv", "data\\stage\\01\\map_textureid.csv", this->vterrain, &this->texture) ? dbg.print("Success!") : dbg.print("Failed...");

	fonthandle.push_back(CreateFontToHandle("メイリオ", 14, 0, DX_FONTTYPE_ANTIALIASING_EDGE));
	fonthandle.push_back(CreateFontToHandle("メイリオ", 20, 0, DX_FONTTYPE_ANTIALIASING_EDGE));
	fonthandle.push_back(CreateFontToHandle("メイリオ", 46, 0, DX_FONTTYPE_ANTIALIASING_EDGE));
}

void Game::Update() {
	/* Mouse */
	this->mouse.update();

	/* Keyboard */
	this->keyboard.update();

	/* Button */
	// button update
	for (auto i = vbutton.begin(); i != vbutton.end(); i++) { (*i)->update(this->mouse); }
	for (auto i = vtbutton.begin(); i != vtbutton.end(); i++) { (*i)->update(); }
	
	// toggle pause
	if (vbutton[0]->isClicked() || keyboard.getPressingCount(KEY_INPUT_SPACE) == 1) { isPaused = isPaused? false : true; }

	// toggle fast forward
	if (vbutton[1]->isClicked() || keyboard.getPressingCount(KEY_INPUT_F) == 1) { ffmul = ffmul == 1 ? 2 : 1; }

	// next wave
	if (vbutton[2]->isClicked() || keyboard.getPressingCount(KEY_INPUT_N) == 1) { ws->nextWave(); }

	// construct turret
	{
		int selectedturret = vtbutton[0]->getChannel();
		if (selectedturret != -1) {

			info.update(vturret_ini[selectedturret]->getStatusText());

			for (int i = 13; i < 134; i++) {
				if (!(vbutton[i]->isClicked()))continue;

				int x = (int)floor((i - 13) / 11);
				int y = (i - 13) % 11;


				if (!vterrain[x][y]->canPlaceTurret())break;

				// construction
				if (!vturret_ini[selectedturret]->canConstruct(this->resource)) {
					vtbutton[0]->clearChannel();
					break;
				}
				this->resource -= vturret_ini[selectedturret]->getConstructCost();

				vturret.push_back(tf->create(vturret_ini[selectedturret]->getName(), this->vpath));

				vturret[(signed)vturret.size() - 1]->setPosition(Vector2D(vbutton[i]->getPosition().getX() + 32, vbutton[i]->getPosition().getY() + 32));
				vterrain[x][y]->changeCanPlaceTurret();

				if (keyboard.getPressingCount(KEY_INPUT_LSHIFT) == 0) {
					vtbutton[0]->clearChannel();
				}
			}
		}
		else {
			for (int i = 13; i < 134; i++) {
				if (!(vbutton[i]->isClicked()))continue;

				int x = (int)floor((i - 13) / 11);
				int y = (i - 13) % 11;

				if (vterrain[x][y]->canPlaceTurret())break;

				// upgrade
				
			}
		}
	}

	/* Not Paused */
	if (isPaused) return;

	for (int i = 0; i < ffmul; i++) {
		ws->update(this->venemy,&this->resource);
	}

	for (auto i = venemy.begin(); i != venemy.end(); i++) {
		if (!(*i)->isAlive()) {
			this->resource += (*i)->getResourcereward();
			continue;
		}
		for (int j = 0; j < ffmul; j++) {
			(*i)->update(vpath, &this->health);
		}
	}
	for (int i = 0; i < (signed)venemy.size(); i++) {
		if (!venemy[i]->isAlive())this->venemy.erase(this->venemy.begin() + i);
	}

	for (auto i = vturret.begin(); i != vturret.end(); i++) {
		for (int j = 0; j < ffmul; j++) {
			(*i)->attack(&venemy, this->sound);
		}
	}

	if (this->health <= 0) {
		MessageBox(nullptr, "You have defeated...", "Game Over", MB_OK);
		mSceneChanger->ChangeMainScene(eEnd);
	}

	if (ws->isFinishedSendEnemy() && venemy.size() == 0) {
		mSceneChanger->ChangeMainScene(eEnd);
	}
}

void Game::Draw() {
	

	// terrain
	for (int i = 0; i < (signed)vterrain.size(); i++) {
		for (int j = 0; j < (signed)vterrain[i].size(); j++) {
			vterrain[j][i]->draw();
		}
	}

	// WaveGuage
	ws->draw(this->texture, Vector2D(8, 56));

	// field
	const int Boxsize = 64;
	for (int i = 0; i < (signed)vterrain.size(); i++) {
		for (int j = 0; j < (signed)vterrain[i].size(); j++) {
			DrawBox(80 + j * Boxsize, 56 + i * Boxsize, 144 + j * Boxsize, 120 + i * Boxsize, White, FALSE);
		}
	}

	

	// overall
	DrawGraph(0, 0, texture.getHandle("texture/Game/Field/overall.png"), TRUE);

	// Money
	DrawStringToHandle(530, 8, "Money", Black, fonthandle[0]);
	DrawFormatStringToHandle(560,26,Black,fonthandle[1],"%d",this->resource);


	// Health
	DrawFormatStringToHandle(666, 8, Black, fonthandle[0], "Health",this->health);
	DrawFormatStringToHandle(706, 26, Black, fonthandle[1], "%d", this->health);

	// turret construction title
	DrawStringToHandle(810, 74, "TURRET", Black, fonthandle[2], White);

	// turrets
	for (auto i = vturret.begin(); i != vturret.end(); i++) {
		(*i)->draw(this->texture);
	}

	// button
	for (auto i = vbutton.begin(); i != vbutton.end(); i++) {
		(*i)->draw();
	}

	// info
	DrawStringToHandle(844, 350, "INFO", Black, fonthandle[2], White);
	if(vtbutton[0]->getChannel() != -1)info.draw(Vector2D(830, 420), Black, INFOTYPE_NONEBORDER, INFOTYPE_CLEARBACK, eTextAlignmentLeft);

	// enemy
	for (auto i = venemy.begin(); i != venemy.end(); i++) {
		if (!(*i)->isAlive())continue;
		(*i)->draw(this->texture);
	}
}

void Game::Finalize() {
	for (auto i = vbutton.begin(); i != vbutton.end(); i++) {
		delete (*i);
	}
	for (auto i = vtbutton.begin(); i != vtbutton.end(); i++) {
		delete (*i);
	}
	for (auto i = vturret.begin(); i != vturret.end(); i++) {
		delete (*i);
	}
	for (int i = 0; i < (signed)vterrain.size(); i++) {
		for (int j = 0; j < (signed)vterrain[i].size(); j++) {
			delete vterrain[j][i];
		}
	}
	for (auto i = vwave.begin(); i != vwave.end(); ++i) {
		delete (*i);
	}

	
	delete this->ws;
	delete this->tf;
	texture.deleteHandleAll();
	MessageBox(nullptr, "Thank you for playing.", "Game Over", MB_OK);
}