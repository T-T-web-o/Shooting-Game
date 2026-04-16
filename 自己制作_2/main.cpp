#include "DxLib.h"
#include "GameManager.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ウインドウモードで起動
	ChangeWindowMode(TRUE);

    // DxLib初期化
    if (DxLib_Init() == -1)
    {
        return -1;
    }

    // 裏画面描画
    SetDrawScreen(DX_SCREEN_BACK);

    // ===== メインループ =====
    while (ProcessMessage() == 0)
    {
        // 画面クリア
        ClearDrawScreen();

        // 更新
        GameManager::GetInstance().Update();

        // 描画
        GameManager::GetInstance().Draw();

        // 画面反映
        ScreenFlip();
    }

	// DxLibの終了処理
	DxLib_End();

	return 0;
}