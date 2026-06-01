#include "Enemy.h"
#include "DxLib.h"
#include <cmath>
#include <cstdlib>

//============================================================
// 定数
//============================================================
const int ENEMY_START_X_RANGE = 450; // 敵の出現X座標の範囲
const int ENEMY_START_Y = -30;       // 敵の初期Y座標（画面外上）

const int NORMAL_RATE = 60;          // NORMALの出現率
const int FAST_RATE = 90;            // FASTの出現率

const int NORMAL_HP = 100;           // 通常敵のHP
const int FAST_HP = 200;             // 高速敵のHP
const int ZIGZAG_HP = 300;           // ジグザグ敵のHP
const int ROTTEN_HP = 100;           // 腐った敵のHP

const int NORMAL_SPEED = 2;          // 通常敵の速度
const int FAST_SPEED = 4;            // 高速敵の速度

const float ZIGZAG_FREQ = 0.05f;     // 揺れの速さ
const int ZIGZAG_AMPLITUDE = 50;     // 横揺れの大きさ

const int SCREEN_HEIGHT = 500;       // 画面の縦幅

//============================================================
// コンストラクタ（敵の初期化）
//============================================================
Enemy::Enemy()
{
	// 初期位置設定
	x = ENEMY_START_X;
	y = ENEMY_START_Y;

	// 生存状態
	isDead = false;

	// ZIGZAG用基準位置
	baseX = x;

	// 敵の出現率を設定
	int r = SPAWN_RATE;
	
	if (r < NORMAL_RATE)
	{
		type = NORMAL;
	}
	else if (r < FAST_RATE)
	{
		type = FAST;
	}
	else
	{
		type = ZIGZAG;
	}

	// 20％の確率で腐る
	isRotten= (rand() % 100 < 20);

	// 体力の初期化
	switch (type)
	{
	case NORMAL:
		hp = NORMAL_HP;
		break;
	case FAST:
		hp = FAST_HP;
		break;
	case ZIGZAG:
		hp = ZIGZAG_HP;
		break;
	}

	// 腐っていたら体力100
	if (isRotten)
	{
		hp = ROTTEN_HP;
	}
}

//============================================================
// 敵の更新処理
//============================================================
void Enemy::Update()
{
	// 種類ごとの動きを設定
	switch (type)
	{
	case NORMAL:
		y += NORMAL_SPEED;
		break;
	case FAST:
		y += FAST_SPEED;
		break;
	case ZIGZAG:
		y += NORMAL_SPEED;
		x = baseX + static_cast<int>(sin(y * ZIGZAG_FREQ) * ZIGZAG_AMPLITUDE);
		break;
	}
	
	// 画面外に出たら削除
	if (y > SCREEN_HEIGHT)
	{
		isDead = true;
	}
}

//============================================================
// 敵の描画処理
//============================================================
void Enemy::Draw(int Image)
{
	// 指定された画像を描画
	DrawGraph(x, y, Image, TRUE);
}
