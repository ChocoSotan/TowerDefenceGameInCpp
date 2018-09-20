#include <Windows.h>

#include "DxLib.h"
#include "GameManager.h"



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	
	SetMainWindowText("Tower Defence Game");
	SetGraphMode(1024, 768, 32);
	SetWindowSize(1024, 768);
	
	DxLib::SetOutApplicationLogValidFlag(FALSE);
	ChangeWindowMode(TRUE); 
	SetDrawScreen(DX_SCREEN_BACK);
	DxLib_Init();

	GameManager gm;
	gm.Initialize();

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {

		gm.Update();
		gm.Draw();

	}

	gm.Finalize();
	DxLib_End();

	return 0;
}