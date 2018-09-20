#pragma once

#include "Scene.h"
#include "DxLib.h"

#include "Debugger.h"
#include "Loader.h"
#include "Texture.h"
#include "Mouse.h"

#include <vector>

class Title : public BaseScene {
public:
	Title(ISceneChanger *changer);
	~Title() {}

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Finalize() override;

private:
	Debugger db;
	Texture texture;
	TextureLoader tl;
	Mouse mouse;

	Button *button_newgame;
	Button *button_left;
	Button *button_right;
	Button *button_end;

	std::vector<int> fonthandle;

	int m_stage;
	int m_stage_max;
};

Title::Title(ISceneChanger *changer) : BaseScene(changer) {
	m_stage = 1;
	m_stage_max = 2;
}

void Title::Initialize() {
	// Loading Texture
	db.print("Initializing texture......");
	tl.load("data/tl/texturelist.csv", &this->texture) ? db.print("Success!") : db.print("Failed...");


	// load title paint
	// texture.pool("texture/title/title.png");

	button_newgame = new Button(384, 364);
	button_end = new Button(384, 364+192);
	button_right = new Button(578+128, 364+64);
	button_left = new Button(320-64, 364+64);

	button_newgame->init(&this->texture, "texture/Title/button/newgame.png");
	button_left->init(&this->texture, "texture/Title/button/left.png");
	button_right->init(&this->texture, "texture/Title/button/right.png");
	button_end->init(&this->texture, "texture/Title/button/endgame.png");

	// fonts
	this->fonthandle.push_back(CreateFontToHandle("ƒƒCƒŠƒI", 64, 1));
}

void Title::Update() {
	mouse.update();

	button_newgame->update(this->mouse);
	button_left->update(this->mouse);
	button_right->update(this->mouse);
	button_end->update(this->mouse);

	if (button_newgame->isClicked()) {
		db.print("Pressed new game button.");
		this->mSceneChanger->ChangeMainScene(eGame);
	}
	if (button_end->isClicked()) {
		db.print("Pressed end game button.");
		this->mSceneChanger->ChangeMainScene(eEnd);
	}
	if (button_right->isClicked()) {
		this->m_stage = this->m_stage % m_stage_max + 1;
	}
	if (button_left->isClicked()) {
		this->m_stage = (this->m_stage + m_stage_max) % m_stage_max + 1;
	}
}

void Title::Draw() {
	// DrawGraph(0, 0, texture.getHandle("texture/title/title.png"), FALSE);

	button_newgame->draw();
	button_end->draw();
	button_left->draw();
	button_right->draw();

	DrawFormatStringToHandle(320+64, 364 + 64, GetColor(255, 255, 255), this->fonthandle[0], "Stage %d", this->m_stage);
}

void Title::Finalize() {
	texture.deleteHandleAll();
}