#include "Enemy.h"
#include "DxLib.h"
#include <cstdlib>

Enemy::Enemy()
{
	x = rand() % 500;
	y = 0;
	Dead = false;
}

void Enemy::Update()
{
	y += 2;
	if (y > 500)
	{
		Dead = false;
	}
}

void Enemy::Draw()
{
	DrawBox(x - 10, y - 10, x + 10, y + 10, GetColor(255, 0, 0), TRUE);
}
