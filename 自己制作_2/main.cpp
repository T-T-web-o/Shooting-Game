#include "DxLib.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ウインドウモードで起動
	ChangeWindowMode(TRUE);

	// DxLib初期化
	DxLib_Init();

	// DxLibの終了処理
	DxLib_End();

	return 0;
}