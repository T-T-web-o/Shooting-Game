#include "Player.h"
#include "DxLib.h"

//============================================================
// 定数
//============================================================
const int PLAYER_START_X = 300;   // プレイヤーの初期X座標
const int PLAYER_START_Y = 300;   // プレイヤーの初期Y座標

const int PLAYER_HP = 10;         // プレイヤーの初期体力

const int PLAYER_SPEED = 5;       // プレイヤーの速度

const int SCREEN_WIDTH = 640;     // 横画面サイズ
const int SCREEN_HEIGHT = 480;    // 縦画面サイズ

//============================================================
// コンストラクタ
//============================================================
Player::Player()
{
	// 位置初期化
	x = PLAYER_START_X;
	y = PLAYER_START_Y;
	
	// 現在の体力
	hp = PLAYER_HP;

	// 無敵時間
	InvincibilityTimer = 0;
}


//============================================================
// 更新処理
//============================================================
void Player::Update()
{
	// 移動
	if (CheckHitKey(KEY_INPUT_A))x -= PLAYER_SPEED;
	if (CheckHitKey(KEY_INPUT_D))x += PLAYER_SPEED;
	if (CheckHitKey(KEY_INPUT_W))y -= PLAYER_SPEED;
	if (CheckHitKey(KEY_INPUT_S))y += PLAYER_SPEED;

	// 画面外防止
	if (x < 0)x = 0;
	if (x > SCREEN_WIDTH)x = SCREEN_WIDTH;
	if (y < 0)y = 0;
	if (y > SCREEN_HEIGHT)y = SCREEN_HEIGHT;

	// 無敵時間を減らす
	if (InvincibilityTimer > 0)
	{
		InvincibilityTimer--;
	}
}


//============================================================
// 描画処理
//============================================================
void Player::Draw(int Image)
{
	// 指定された画像を描画
	DrawGraph(x, y, Image, TRUE);
}
