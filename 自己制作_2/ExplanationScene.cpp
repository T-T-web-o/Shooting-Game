#include "ExplanationScene.h"
#include "GameScene.h"
#include "GameManager.h"
#include "Player.h"
#include "DxLib.h"

const int GUIDE_TITLE_X = 220;       // 「ゲーム説明」タイトルのX座標
const int GUIDE_TITLE_Y = 10;        // 「ゲーム説明」タイトルのY座標

const int GUIDE_TEXT_X = 100;        // 説明のX座標
const int GUIDE_TEXT_Y_START = 90;   // 操作説明のY座標
const int GUIDE_TEXT_SPACE = 35;     // 操作説明同士の間隔

const int START_TEXT_X = 250;        // 「Enterでゲームスタート」のX座標
const int START_TEXT_Y = 450;        // 「Enterでゲームスタート」のY座標

// 操作機体
const int PLAYER_TEXT_X = 430;       // 「操作機体」のX座標
const int PLAYER_TEXT_Y = 90;        // 「操作機体」のY座標
const int PLAYER_IMG_X = 470;        // 機体画像のX座標
const int PLAYER_IMG_Y = 165;        // 機体画像のY座標
const double PLAYER_SCALE = 1.6;     // 画像の大きさ

// 敵
const int ENEMY_TEXT_X = 430;        // 「敵」のX座標
const int ENEMY_TEXT_Y = 240;        // 「敵」のY座標
const int ENEMY1_X = 470;            // 敵１画像のX座標 
const int ENEMY2_X = 540;            // 敵２画像のY座標
const int ENEMY_Y = 290;             // 敵画像のY座標

// HPバー
const int HP_TEXT_X = 430;           // 「HPバー」のX座標
const int HP_TEXT_Y = 400;           // 「HPバー」のY座標
const int HP_BLOCK_WIDTH = 30;       // 黒いHPバーの幅
const int HP_BLOCK_HEIGHT = 20;      // 黒いHPバーの高さ
const int HP_MAX = 10;               // 最大体力

const int COLOR_TEXT = GetColor(0, 0, 0);  // 黒

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
    DrawString(GUIDE_TITLE_X, GUIDE_TITLE_Y, TEXT("ゲーム説明"), COLOR_TEXT);

    SetFontSize(20); 
   
    // ゲーム説明テキストの表示
    for (int i = 0; i < GUIDE_COUNT; i++)
    {
        DrawString(GUIDE_TEXT_X, GUIDE_TEXT_Y_START + GUIDE_TEXT_SPACE * i, guideText[i], COLOR_TEXT);
    }
  
    // スタート案内
    DrawString(START_TEXT_X, START_TEXT_Y, TEXT("EnterでGameスタート"), COLOR_TEXT);

    // 操作機体表示
    DrawString(PLAYER_TEXT_X, PLAYER_TEXT_Y, TEXT("操作機体"), COLOR_TEXT);

    DrawRotaGraph(PLAYER_IMG_X, PLAYER_IMG_Y, PLAYER_SCALE, 0.0, playerImage, TRUE);

    // 敵表示
    DrawString(ENEMY_TEXT_X, ENEMY_TEXT_Y, TEXT("敵"), COLOR_TEXT);

    DrawRotaGraph(ENEMY1_X, ENEMY_Y, 1.0, 0.0, enemyImage1, TRUE);
    DrawRotaGraph(ENEMY2_X, ENEMY_Y, 1.0, 0.0, enemyImage2, TRUE);

    // 体力バー
    DrawString(HP_TEXT_X, HP_TEXT_Y, TEXT("HPバー(初期HP : 10)"), COLOR_TEXT);

    int x = 330; int y = 420; // 表示位置

    DrawBox(x, y, x + 10 * HP_BLOCK_WIDTH, y + HP_BLOCK_HEIGHT, COLOR_TEXT, TRUE);

    for (int i = 0; i < HP_MAX; i++)
    {
        int r = 255 * (HP_MAX - i) / HP_MAX; // RGB値を計算
        int g = 255 * i / HP_MAX;
        int b = 0;
        DrawBox(x + 2 + i * 30, y + 2, x + 28 + i * 30, y + 18, GetColor(r, g, b), TRUE);
    }
}
