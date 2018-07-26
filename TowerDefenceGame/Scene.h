#pragma once

#include "ISceneChanger.h"
#include "Task.h"

class BaseScene : public Task {
public:
	BaseScene(ISceneChanger* changer);
	virtual ~BaseScene() {}
	virtual void Initialize() override {}
	virtual void Finalize() override;
	virtual void Update() override {}
	virtual void Draw() override;

protected:
	ISceneChanger *mSceneChanger;    //�N���X���L���ɃV�[���؂�ւ���`����C���^�[�t�F�C�X
};

BaseScene::BaseScene(ISceneChanger *changer) {
	this->mSceneChanger = changer;
}
