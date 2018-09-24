#pragma once

#include "Scene.h"
#include "DxLib.h"

#include "Debugger.h"

#include "Texture.h"
#include "Button.h"

#include "TextureLoader.h"

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

	// buttons
	Button button_newgame = Button(384, 364);
	Button button_left = Button(320 - 64, 364 + 64);
	Button button_right = Button(578 + 128, 364 + 64);
	Button button_end = Button(384, 364 + 192);

	// fonts
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
	tl.load("data/texturelist/title.csv", &this->texture) ? db.print("Success!") : db.print("Failed...");

	button_newgame.init(this->texture, "texture/Title/button/newgame.png");
	button_left.init(this->texture, "texture/Title/button/left.png");
	button_right.init(this->texture, "texture/Title/button/right.png");
	button_end.init(this->texture, "texture/Title/button/endgame.png");

	// fonts
	this->fonthandle.push_back(CreateFontToHandle("ƒƒCƒŠƒI", 64, 1,DX_FONTTYPE_ANTIALIASING_EDGE));
}

void Title::Update() {
	mouse.update();

	button_newgame.update(this->mouse);
	button_left.update(this->mouse);
	button_right.update(this->mouse);
	button_end.update(this->mouse);

	if (button_newgame.isClicked()) {
		db.print("Pressed new game button.");
		this->mSceneChanger->ChangeMainScene(eGame);
	}
	if (button_end.isClicked()) {
		db.print("Pressed end game button.");
		this->mSceneChanger->ChangeMainScene(eEnd);
	}
	if (button_right.isClicked()) {
		this->m_stage = this->m_stage % m_stage_max + 1;
	}
	if (button_left.isClicked()) {
		this->m_stage = (this->m_stage + m_stage_max) % m_stage_max + 1;
	}
}

void Title::Draw() {
	DrawGraph(0, 0, texture.getHandle("texture/Title/title.png"), FALSE);

	button_newgame.draw(this->texture);
	button_end.draw(this->texture);
	button_left.draw(this->texture);
	button_right.draw(this->texture);

	DrawFormatStringToHandle(320+64, 364 + 64, GetColor(255, 255, 255), this->fonthandle[0], "Stage %d", this->m_stage);
}

void Title::Finalize() {
	texture.deleteHandleAll();
	for (auto i = this->fonthandle.begin(); i != fonthandle.end(); ++i) {
		DeleteFontToHandle((*i));
	}
}