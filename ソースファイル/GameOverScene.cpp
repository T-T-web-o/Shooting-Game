#include "GameOverScene.h"
#include "GameManager.h"
#include "TitleScene.h"
#include "DxLib.h"

//============================================================
// 描画用定数
//============================================================

const int TITLE_TEXT_X = 230; // タイトル文字のX座標
const int TITLE_TEXT_Y = 200; // タイトル文字のY座標

const int GUIDE_X = 450;      // 操作案内X座標
const int GUIDE_Y = 460;      // 操作案内Y座標

//============================================================
// コンストラクタ
//============================================================
GameOverScene::GameOverScene()
{
    // 画面サイズ取得
    GetDrawScreenSize(&screenW, &screenH);

    // 背景画像読み込み
    bgImage = LoadGraph(TEXT("Resource/Model/GameOver.png"));
}

//===========================================================
// デストラクタ(使用した画像の解放)
//===========================================================
GameOverScene::~GameOverScene()
{
    DeleteGraph(bgImage);
}

//============================================================
// 更新処理
//============================================================
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

//============================================================
// 描画処理
//============================================================
void GameOverScene::Draw()
{
    // 背景画像の描画
    DrawExtendGraph(0, 0, screenW, screenH, bgImage, TRUE);

    // GAME OVER を描画
    SetFontSize(40);
    DrawString(TITLE_TEXT_X, TITLE_TEXT_Y, TEXT("GAME OVER"), GetColor(255, 0, 0));

    // 操作案内
    SetFontSize(15);
    DrawString(GUIDE_X, GUIDE_Y, TEXT("Press Enter to Title"), GetColor(255, 255, 255));
}
