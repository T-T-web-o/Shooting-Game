#include "GameOverScene.h"
#include "GameManager.h"
#include "TitleScene.h"
#include "DxLib.h"

GameOverScene::GameOverScene()
{
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
    DrawGraph(0, 0, bgImage, TRUE);

    // GAME OVER を描画
    DrawString(250, 200, TEXT("GAME OVER"), GetColor(255, 0, 0));

    // 操作案内
    DrawString(150, 300, TEXT("Press Enter to Title"), GetColor(255, 255, 255));
}
