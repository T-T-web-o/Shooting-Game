#include "Enemy.h"
#include "DxLib.h"
#include <cmath>
#include <cstdlib>

Enemy::Enemy()
{
	// 初期位置設定
	x = rand() % 450;
	y = -30;

	// 生存状態
	isDead = false;

	// ZIGZAG用基準位置
	baseX = x;

	// 敵の出現率を設定
	int r = rand() % 100;
	
	if (r < 60)
	{
		type = NORMAL;
	}
	else if (r < 90)
	{
		type = FAST;
	}
	else
	{
		type = ZIGZAG;
	}


	// 体力の初期化
	switch (type)
	{
	case NORMAL:
		hp = 1;
		break;
	case FAST:
		hp = 2;
		break;
	case ZIGZAG:
		hp = 2;
		break;
	}
}

void Enemy::Update()
{
	// 種類ごとの動きを設定
	switch (type)
	{
	case NORMAL:
		y += 2;
		break;
	case FAST:
		y += 4;
		break;
	case ZIGZAG:
		y += 2;
		x = baseX + static_cast<int>(sin(y * 0.05) * 50);
		break;
	}
	
	// 画面外に出たら削除
	if (y > 500)
	{
		isDead = true;
	}
}

void Enemy::Draw(int Image)
{
	// 指定された画像を描画
	DrawGraph(x, y, Image, TRUE);
}
