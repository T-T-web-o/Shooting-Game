#include "Bullet.h"
#include "GameScene.h"
#include "DxLib.h"

Bullet::Bullet(int startX, int startY)
{
	x = startX;
	y = startY;
	Dead = false;
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	y -= 10;

	if (y < 0)
	{
		Dead = true;
	}
}

void Bullet::Draw(int Image)
{
	DrawGraph(x, y, Image, TRUE);
}
