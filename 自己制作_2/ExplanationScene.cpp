#include "ExplanationScene.h"
#include "GameScene.h"
#include "GameManager.h"
#include "Player.h"
#include "DxLib.h"

const int GUIDE_TITLE_X = 220;             // 「ゲーム説明」タイトルのX座標
const int GUIDE_TITLE_Y = 10;              // 「ゲーム説明」タイトルのY座標

const int GUIDE_TEXT_X = 100;              // 説明のX座標
const int GUIDE_TEXT_Y_START = 90;       // 操作説明のY座標
const int GUIDE_TEXT_SPACE = 35;         // 操作説明同士の間隔

// ゲーム説明テキスト一覧
const TCHAR* guideText[] =
{
    TEXT("[操作方法]"),
    TEXT("WASD : 移動"),
    TEXT("SPACE : 攻撃"),
    TEXT("[ルール]"),
    TEXT("敵を倒してスコアを稼ごう"),
    TEXT("ボスを倒すとクリア"),
    TEXT("[ヒント]"),
    TEXT("敵を避けながら戦おう"),
    TEXT("HPが0になるとゲームオーバー"),
};

// 配列の要素数を自動で取得
const int GUIDE_COUNT = sizeof(guideText) / sizeof(guideText[0]);

ExplanationScene::ExplanationScene()
{
    // 画面サイズ取得
    GetDrawScreenSize(&screenW, &screenH);

    // 背景画像読み込み
    bgImage = LoadGraph(TEXT("Resource/Explanation.png"));
    playerImage = LoadGraph(TEXT("Resource/player.png"));
    enemyImage1 = LoadGraph(TEXT("Resource/enemy1.png"));
    enemyImage2 = LoadGraph(TEXT("Resource/enemy2.png"));
}


ExplanationScene::~ExplanationScene()
{
    // 使用した画像の解放
    DeleteGraph(bgImage);
    DeleteGraph(playerImage);
    DeleteGraph(enemyImage1);
    DeleteGraph(enemyImage2);
}

void ExplanationScene::Update()
{
    // Enterキー入力取得
    nowEnter = (CheckHitKey(KEY_INPUT_RETURN));

    // Enterキーが押されたか判定
    if (nowEnter && !prevEnter)
    {
        // ゲームシーンに移行
        GameManager::GetInstance().ChangeScene(std::make_unique<GameScene>());
    }
    // 前フレームの入力を保存
    prevEnter = nowEnter;
}

void ExplanationScene::Draw()
{
    // 背景画像の描画
    DrawExtendGraph(0, 0, screenW, screenH, bgImage, TRUE);

    SetFontSize(40); 
    // ゲーム説明
    DrawString(GUIDE_TITLE_X, GUIDE_TITLE_Y, TEXT("ゲーム説明"), GetColor(0, 0, 0));

    SetFontSize(20); 
   
    // ゲーム説明テキストの表示
    for (int i = 0; i < GUIDE_COUNT; i++)
    {
        DrawString(GUIDE_TEXT_X, GUIDE_TEXT_Y_START + GUIDE_TEXT_SPACE * i, guideText[i], GetColor(0, 0, 0));
    }
  
    DrawString(250, 450, TEXT("EnterでGameへ"), GetColor(255, 255, 255));

    // 操作機体表示
    DrawString(430, 90, TEXT("操作機体"), GetColor(0, 0, 0));

    DrawRotaGraph(470, 165, 1.6, 0.0, playerImage, TRUE);

    // 敵表示
    DrawString(430, 240, TEXT("敵"), GetColor(0, 0, 0));

    DrawRotaGraph(470, 290, 1.0, 0.0, enemyImage1, TRUE);
    DrawRotaGraph(540, 290, 1.0, 0.0, enemyImage2, TRUE);

    // 体力バー
    DrawString(430, 400, TEXT("HPバー(初期HP : 10)"), GetColor(0, 0, 0));

    int x = 330; int y = 420; // 表示位置
    DrawBox(x, y, x + 10 * 30, y + 20, GetColor(0, 0, 0), TRUE);
    for (int i = 0; i < 10; i++)
    {
        int r = 255 * (10 - i) / 10; // RGB値を計算
        int g = 255 * i / 10;
        int b = 0;
        DrawBox(x + 2 + i * 30, y + 2, x + 28 + i * 30, y + 18, GetColor(r, g, b), TRUE);
    }
}
