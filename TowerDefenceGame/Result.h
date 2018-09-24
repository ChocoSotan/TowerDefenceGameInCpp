#pragma once

#include "Scene.h"

#include "Texture.h"
#include "TextureLoader.h"
#include "Debugger.h"
#include "Button.h"
#include "Mouse.h"

class Result : public BaseScene {
public:
	Result(ISceneChanger *changer);
	~Result() {}

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
	Button button_title = Button(512-98,384);
	Button button_end = Button(512-98,384+64*2);


	// fonts
	std::vector<int> fonthandle;

	int m_stage;
	int m_stage_max;
};

Result::Result(ISceneChanger *changer) : BaseScene(changer) {

}

void Result::Initialize() {
	db.print("Initializing Result...");
	tl.load("data/texturelist/result.csv", &this->texture) ? db.print("Success!") : db.print("Failed...");


	button_title.init(this->texture, "texture/Result/button/title.png");
	button_end.init(this->texture, "texture/Result/button/endgame.png");
}

void Result::Update() {
	mouse.update();
	button_title.update(mouse);
	button_end.update(mouse);

	if (button_title.isClicked()) {
		db.print("Go to Title.");
		mSceneChanger->ChangeMainScene(eTitle);
	}
	if (button_end.isClicked()) {
		db.print("End Game.");
		mSceneChanger->ChangeMainScene(eEnd);
	}
}

void Result::Draw() {
	button_title.draw(this->texture);
	button_end.draw(this->texture);
}

void Result::Finalize() {
	for (auto i = this->fonthandle.begin(); i != fonthandle.end(); ++i) {
		DeleteFontToHandle((*i));
	}
}
