#include "GameOverScene.h"
#include "GameManager.h"
#include "TitleScene.h"
#include "DxLib.h"

GameOverScene::GameOverScene()
{
    // 画面サイズ取得
    GetDrawScreenSize(&screenW, &screenH);

    // 背景画像読み込み
    bgImage = LoadGraph(TEXT("Resource/GameOver.png"));
}

// 使用した画像の解放
GameOverScene::~GameOverScene()
{
    DeleteGraph(bgImage);
}

void GameOverScene::Update()
{
    // Enterキー入力取得
    nowEnter = (CheckHitKey(KEY_INPUT_RETURN));

    // Enterキーが押されたか判定
    if (nowEnter && !prevEnter)
    {
        // タイトルシーンへ移行
        GameManager::GetInstance().ChangeScene(std::make_unique<TitleScene>());
    }
    // 前フレームの入力を保存
    prevEnter = nowEnter;
}

void GameOverScene::Draw()
{
    // 背景画像の描画
    DrawExtendGraph(0, 0, screenW, screenH, bgImage, TRUE);

    // GAME OVER を描画
    SetFontSize(40);
    DrawString(230, 200, TEXT("GAME OVER"), GetColor(255, 0, 0));

    // 操作案内
    SetFontSize(15);
    DrawString(450, 460, TEXT("Press Enter to Title"), GetColor(255, 255, 255));
}
