#include "ClearScene.h"
#include "DxLib.h"
#include "TitleScene.h"
#include "GameManager.h"

void ClearScene::Update()
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

void ClearScene::Draw()
{
    // GAME CLEARを描画
    DrawString(150, 200, TEXT("GAME CLEAR"), GetColor(255, 255, 0));
    
    // 操作案内
    DrawString(150, 300, TEXT("Press Enter to Title"), GetColor(255, 255, 255));
}
