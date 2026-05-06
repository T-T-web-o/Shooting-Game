#include "TitleScene.h"
#include "GameManager.h"
#include "GameScene.h"
#include "ExplanationScene.h"
#include "DxLib.h"

const int GUIDE_X = 450;
const int GUIDE_Y = 450;

TitleScene::TitleScene()
{
   isReady = false;

   // 画面サイズ取得
   GetDrawScreenSize(&screenW, &screenH);

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
        GameManager::GetInstance().ChangeScene(std::make_unique<ExplanationScene>());
    }
    // 前フレームの入力を保存
    prevEnter = nowEnter;
}

void TitleScene::Draw()
{
    // 背景画像の描画
    DrawExtendGraph(0, 0, screenW, screenH, titleImage, TRUE);

    SetFontSize(30);
    DrawString(GUIDE_X, GUIDE_Y, TEXT("Press Enter"), GetColor(0, 0, 0));
}
