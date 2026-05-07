#include "GameClearScene.h"
#include "DxLib.h"
#include "TitleScene.h"
#include "GameManager.h"
#include "ResultScene.h"

//============================================================
// 描画用定数
//============================================================

const int TITLE_TEXT_X = 230; // タイトル文字のX座標
const int TITLE_TEXT_Y = 200; // タイトル文字のY座標

const int GUIDE_X = 450;      // 操作案内のX座標
const int GUIDE_Y = 450;      // 操作案内のY座標

GameClearScene::GameClearScene()
{
    // 画面サイズ取得
    GetDrawScreenSize(&screenW, &screenH);

    // 背景画像読み込み
    bgImage = LoadGraph(TEXT("Resource/GameClear.png"));
}

//============================================================
// デストラクタ(使用した画像の解放)
//============================================================
GameClearScene::~GameClearScene()
{
    // 使用した画像の解放
    DeleteGraph(bgImage);
}

//============================================================
// 更新処理
//============================================================
void GameClearScene::Update()
{
    // Enterキー入力取得
    nowEnter = (CheckHitKey(KEY_INPUT_RETURN));

    // Enterキーが押されたか判定
    if (nowEnter && !prevEnter)
    {
        // タイトルシーンに移行
        GameManager::GetInstance().ChangeScene(std::make_unique<ResultScene>());
    }
    // 前フレームの入力を保存
    prevEnter = nowEnter;
}

//============================================================
// 描画処理
//============================================================
void GameClearScene::Draw()
{
    // 背景画像の描画
    DrawExtendGraph(0, 0, screenW, screenH, bgImage, TRUE);

    // GAME CLEARを描画
    SetFontSize(40);
    DrawString(TITLE_TEXT_X, TITLE_TEXT_Y, TEXT("GAME CLEAR"), GetColor(255, 255, 0));
    
    // 操作案内
    SetFontSize(15);
    DrawString(GUIDE_X, GUIDE_Y, TEXT("Press Enter to Title"), GetColor(255, 255, 255));
}
