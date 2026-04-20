#include "GameOverScene.h"
#include "GameManager.h"
#include "TitleScene.h"
#include "DxLib.h"

void GameOverScene::Update()
{
    // Enterキー入力取得
    nowEnter = (CheckHitKey(KEY_INPUT_RETURN));

    // Enterキーが押されたか判定
    if (nowEnter && !prevEnter)
    {
        GameManager::GetInstance().ChangeScene(std::make_unique<TitleScene>());
    }
    // 前フレームの入力を保存
    prevEnter = nowEnter;
}

void GameOverScene::Draw()
{
    DrawString(150, 200, TEXT("GAME OVER"), GetColor(255, 0, 0));
    DrawString(150, 300, TEXT("Press Enter to Title"), GetColor(255, 255, 255));
}
