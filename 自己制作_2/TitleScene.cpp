#include "TitleScene.h"
#include "GameManager.h"
#include "GameScene.h"
#include "DxLib.h"

TitleScene::TitleScene()
{
   isReady = false;
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
    int color = GetColor(255, 255, 255);

    SetFontSize(50);
    DrawString(150, 130, TEXT("SHOOTING GAME"), color);

    SetFontSize(30);
    DrawString(150, 300, TEXT("Press Enter"), color);
}
