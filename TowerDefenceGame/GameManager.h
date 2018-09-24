#pragma once

#include "ISceneChanger.h"
#include "Scene.h"
#include "Task.h"

#include "Title.h"
#include "Game.h"
#include "Result.h"

#include "DxLib.h"

class GameManager : public ISceneChanger, Task {

private:
	BaseScene *mScene;
	eMainScene mNextScene;

public:
	GameManager();
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;

	void ChangeMainScene(eMainScene NextScene) override;

};

GameManager::GameManager() : mNextScene(eNone) {
	mScene = (BaseScene*) new Title(this);
}

void GameManager::Initialize() {
	mScene->Initialize();
}

void GameManager::Finalize() {
	mScene->Finalize();
}

void GameManager::Update() {
	if (mNextScene != eNone) {
		mScene->Finalize();
		delete mScene;
		switch (mNextScene) {
		case eTitle:
			mScene = (BaseScene*) new Title(this);
			break;
		case eGame:
			mScene = (BaseScene*) new Game(this, 1);
			break;
		case eResult:
			mScene = (BaseScene*) new Result(this);
			break;
		case eOption:
			//mScene = (BaseScene*) new TitleOption(this);
			break;
		case eEnd:
			DxLib_End();
			exit(EXIT_SUCCESS);
			return;
		}
		mNextScene = eNone;
		mScene->Initialize();
	}

	mScene->Update();
}

//•`‰æ
void GameManager::Draw() {
	mScene->Draw();
}

// ˆø” nextScene ‚ÉƒV[ƒ“‚ğ•ÏX‚·‚é
void GameManager::ChangeMainScene(eMainScene NextScene) {
	mNextScene = NextScene;
}