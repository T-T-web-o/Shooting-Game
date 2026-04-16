#include "Bullet.h"
#include "DxLib.h"

Bullet::Bullet(int startX, int startY)
{
	x = startX;
	y = startY;
	Dead = false;
}

void Bullet::Update()
{
	y -= 10;

	if (y < 0)
	{
		Dead = true;
	}
}

void Bullet::Draw()
{
	DrawCircle(x, y, 5, GetColor(255, 0, 0), TRUE);
}
