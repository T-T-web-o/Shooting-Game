#include "GameClearScene.h"
#include "DxLib.h"
#include "TitleScene.h"
#include "GameManager.h"

GameClearScene::GameClearScene()
{
    // 背景画像読み込み
    bgImage = LoadGraph(TEXT("Resource/GameClear.png"));
}

GameClearScene::~GameClearScene()
{
    DeleteGraph(bgImage);
}

void GameClearScene::Update()
{
    // Enterキー入力取得
    nowEnter = (CheckHitKey(KEY_INPUT_RETURN));

    // Enterキーが押されたか判定
    if (nowEnter && !prevEnter)
    {
        // タイトルシーンに移行
        GameManager::GetInstance().ChangeScene(std::make_unique<TitleScene>());
    }
    // 前フレームの入力を保存
    prevEnter = nowEnter;
}

void GameClearScene::Draw()
{
    // 背景画像の描画
    DrawGraph(0, 0, bgImage, TRUE);

    // GAME CLEARを描画
    SetFontSize(40);
    DrawString(230, 200, TEXT("GAME CLEAR"), GetColor(255, 255, 0));
    
    // 操作案内
    SetFontSize(15);
    DrawString(450, 450, TEXT("Press Enter to Title"), GetColor(255, 255, 255));
}
