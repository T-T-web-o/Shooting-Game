#include "ExplanationScene.h"
#include "GameScene.h"
#include "GameManager.h"
#include "Player.h"
#include "DxLib.h"

const int GUIDE_TITLE_X = 220;             // 「ゲーム説明」タイトルのX座標
const int GUIDE_TITLE_Y = 10;              // 「ゲーム説明」タイトルのY座標

const int GUIDE_TEXT_X = 100;              // 説明文のX座標
const int GUIDE_TEXT_Y = 40;               // 説明文のY座標

ExplanationScene::ExplanationScene()
{
    // 画面サイズ取得
    GetDrawScreenSize(&screenW, &screenH);

    // 背景画像読み込み
    bgImage = LoadGraph(TEXT("Resource/Explanation.png"));
    playerImage = LoadGraph(TEXT("Resource/player.png"));
    enemyImage1 = LoadGraph(TEXT("Resource/enemy1.png"));
    enemyImage2 = LoadGraph(TEXT("Resource/enemy2.png"));

    page = 0;
}

ExplanationScene::~ExplanationScene()
{
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
   
    DrawString(100, 90, TEXT("操作方法"), GetColor(0, 0, 0));

    DrawString(100, 130, TEXT("WASD : 移動"), GetColor(0, 0, 0));
    DrawString(100, 160, TEXT("SPACE : 攻撃"), GetColor(0, 0, 0));

    DrawString(100, 200, TEXT("ルール"), GetColor(0, 0, 0));

    DrawString(100, 240, TEXT("敵を倒してスコアを稼ごう"), GetColor(0, 0, 0));
    DrawString(100, 270, TEXT("ボスを倒すとクリア"), GetColor(0, 0, 0));

    DrawString(100, 310, TEXT("ヒント"), GetColor(0, 0, 0));

    DrawString(100, 350, TEXT("敵を避けながら戦おう"), GetColor(0, 0, 0));
    DrawString(100, 380, TEXT("HPが0になるとゲームオーバー"), GetColor(0, 0, 0));

    DrawString(250, 450, TEXT("EnterでGameへ"), GetColor(255, 255, 255));

    // 操作機体表示
    DrawString(430, 90, TEXT("操作機体"), GetColor(0, 0, 0));

    DrawRotaGraph(470, 165, 1.6, 0.0, playerImage, TRUE);

    // 敵表示
    DrawString(430, 230, TEXT("敵"), GetColor(0, 0, 0));

    DrawRotaGraph(470, 280, 1.0, 0.0, enemyImage1, TRUE);
    DrawRotaGraph(540, 280, 1.0, 0.0, enemyImage2, TRUE);

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
