#include "Bullet.h"
#include "GameScene.h"
#include "DxLib.h"

Bullet::Bullet(int startX, int startY)
{
	// 初期位置設定
	x = startX;
	y = startY;

	// ダメ―ジを設定
	damage = 1;

	// 生存状態
	isDead = false;
}

void Bullet::Update()
{
	// 上に移動
	y -= 10;

	// 画面外に出たら削除
	if (y < 0)
	{
		isDead = true;
	}
}

void Bullet::Draw(int Image)
{
	// 指定された画像を描画
	DrawGraph(x, y, Image, TRUE);
}
