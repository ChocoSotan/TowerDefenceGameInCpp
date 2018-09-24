#pragma once

#include "ISceneChanger.h"
#include "Scene.h"
#include "Task.h"

#include "Title.h"
#include "Game.h"
#include "Result.h"

#include "DxLib.h"

#ifdef _DEBUG
#include <crtdbg.h>
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif // _DEBUG

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

//�`��
void GameManager::Draw() {
	mScene->Draw();
}

// ���� nextScene �ɃV�[����ύX����
void GameManager::ChangeMainScene(eMainScene NextScene) {
	mNextScene = NextScene;
}