#include "ResultScene.h"
#include "DxLib.h"
#include "TitleScene.h"
#include "GameManager.h"

ResultScene::ResultScene()
{
    // 画面サイズ取得
    GetDrawScreenSize(&screenW, &screenH);

    // 背景画像読み込み
    bgImage = LoadGraph(TEXT("Resource/.png"));

    // ゲームシーンのスコアを取得
    score = GameManager::GetInstance().GetScore();
}

ResultScene::~ResultScene()
{
    // 使用した画像の開放
    DeleteGraph(bgImage);
}

void ResultScene::Update()
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

void ResultScene::Draw()
{
    // 背景画像の描画
    DrawExtendGraph(0, 0, screenW, screenH, bgImage, TRUE);
    
    // スコア表示
    DrawFormatString(200, 150, GetColor(255, 255, 255), TEXT("score: %d"), score);
}
