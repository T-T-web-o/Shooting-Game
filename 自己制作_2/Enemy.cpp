#include "Enemy.h"
#include "DxLib.h"
#include <cstdlib>

Enemy::Enemy()
{
	x = rand() % 450;
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

void Enemy::Draw(int Image)
{
	DrawGraph(x, y, Image, TRUE);
}
