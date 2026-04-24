#include "TitleScene.h"
#include "GameManager.h"
#include "GameScene.h"
#include "DxLib.h"

TitleScene::TitleScene()
{
   isReady = false;

   // 背景画像読み込み
   titleImage = LoadGraph(TEXT("Resource/title.png"));
}

// 使用した画像の解放
TitleScene::~TitleScene()
{
    DeleteGraph(titleImage);
}

void TitleScene::Update()
{
    if (!isReady)
    {
        if (!CheckHitKey(KEY_INPUT_RETURN))
        {
            isReady = true;
        }
        return;
    }
    // Enterキー入力取得
    nowEnter = (CheckHitKey(KEY_INPUT_RETURN));

    // Enterキーが押されたか判定
    if (nowEnter && !prevEnter)
    {
        GameManager::GetInstance().ChangeScene(std::make_unique<GameScene>());
    }
    // 前フレームの入力を保存
    prevEnter = nowEnter;
}

void TitleScene::Draw()
{
    // 背景画像の描画
    DrawGraph(0, 0, titleImage, TRUE);

    SetFontSize(30);
    DrawString(450, 450, TEXT("Press Enter"), GetColor(0, 0, 0));
}
