#include "TitleScene.h"
#include "GameManager.h"
#include "GameScene.h"
#include "ExplanationScene.h"
#include "SoundManager.h"
#include "DxLib.h"

//============================================================
// 描画用定数
//============================================================
const int GUIDE_X = 450; // 操作案内のX座標
const int GUIDE_Y = 450; // 操作案内のY座標


TitleScene::TitleScene()
{
   isReady = false;

   // 画面サイズ取得
   GetDrawScreenSize(&screenW, &screenH);

   // 背景画像読み込み
   titleImage = LoadGraph(TEXT("Resource/Model/title.png"));
}

//============================================
// デストラクタ(使用した画像の解放)
//===========================================
TitleScene::~TitleScene()
{
    DeleteGraph(titleImage);
}

//============================================================
// 更新処理
//============================================================
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
        // 効果音再生
        PlaySoundMem(SoundManager::titleSE, DX_PLAYTYPE_BACK);

        GameManager::GetInstance().ChangeScene(std::make_unique<ExplanationScene>());
    }
    // 前フレームの入力を保存
    prevEnter = nowEnter;
}


//============================================================
// 描画処理
//============================================================
void TitleScene::Draw()
{
    // 背景画像の描画
    DrawExtendGraph(0, 0, screenW, screenH, titleImage, TRUE);

    SetFontSize(30);
    DrawString(GUIDE_X, GUIDE_Y, TEXT("Press Enter"), GetColor(0, 0, 0));
}
