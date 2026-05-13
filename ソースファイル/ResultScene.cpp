#include "ResultScene.h"
#include "DxLib.h"
#include "TitleScene.h"
#include "GameManager.h"

//============================================================
// 描画用定数
//============================================================

const int TITLE_TEXT_X = 200; // タイトル文字のX座標
const int TITLE_TEXT_Y = 10;  // タイトル文字のY座標


const int SCORE_TEXT_X = 230; // スコア文字のX座標
const int SCORE_TEXT_Y = 130; // スコア文字のY座標


const int SCORE_X = 150;      // スコア数値のX座標
const int SCORE_Y = 210;      // スコア数値のY座標


const int GUIDE_X = 450;      // 操作案内のX座標
const int GUIDE_Y = 450;      // 操作案内のY座標

// 文字の色
const int TEXT_COLOR = GetColor(0, 0, 0);

// スコアの色
const int SCORE_COLOR = GetColor(0, 255, 0);

// 操作案内文字の色
const int GUIDE_COLOR = GetColor(100, 100, 0);


//============================================================
// コンストラクタ
//============================================================
ResultScene::ResultScene()
{
    // 画面サイズ取得
    GetDrawScreenSize(&screenW, &screenH);

    // 背景画像読み込み
    bgImage = LoadGraph(TEXT("Resource/Model/background.png"));

    // ゲームシーンのスコアを取得
    score = GameManager::GetInstance().GetScore();
}


//============================================================
// デストラクタ
//============================================================
ResultScene::~ResultScene()
{
    // 使用した画像の開放
    DeleteGraph(bgImage);
}


//============================================================
// 更新処理
//============================================================
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


//============================================================
// 描画処理
//============================================================
void ResultScene::Draw()
{
    // 背景画像の描画
    DrawExtendGraph(0, 0, screenW, screenH, bgImage, TRUE);
    
    // リザルト表示
    SetFontSize(70);
    DrawString(TITLE_TEXT_X, TITLE_TEXT_Y, TEXT("RESULT"), TEXT_COLOR);

    // スコア表示
    SetFontSize(60);
    DrawString(SCORE_TEXT_X, SCORE_TEXT_Y, TEXT("SCORE"), TEXT_COLOR);

    SetFontSize(180);
    DrawFormatString(SCORE_X, SCORE_Y, SCORE_COLOR, TEXT("%d"), score);

    // 操作案内
    SetFontSize(30);
    DrawString(GUIDE_X, GUIDE_Y, TEXT("Press Enter"), GUIDE_COLOR);
}
