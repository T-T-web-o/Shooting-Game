#include "DxLib.h"
#include "GameManager.h"
#include "SoundManager.h"
#include "Input.h"

//============================================================
// アプリケーションのエントリーポイント
// Windowsアプリの main 関数
//============================================================
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

    // サウンド読み込み
    SoundManager::Load();

    // ===== メインループ =====
    while (ProcessMessage() == 0)
    {
        // 画面クリア
        ClearDrawScreen();

        // 入力処理更新
        Input::Update();

        // 更新
        GameManager::GetInstance().Update();

        // 描画
        GameManager::GetInstance().Draw();

        // 画面反映
        ScreenFlip();
    }

    // サウンド解放
    SoundManager::Release();

	// DxLibの終了処理
	DxLib_End();

	return 0;
}