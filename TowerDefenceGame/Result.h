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
	Button title = Button(512-98,384);


	// fonts
	std::vector<int> fonthandle;

	int m_stage;
	int m_stage_max;
};

void Result::Initialize() {
	db.print("Initializing Result...");
	tl.load("", &this->texture);
	title.init(&this->texture, "texture/Result/title.png");
}

void Result::Update() {

}

void Result::Draw() {

}
