#include "Enemy.h"
#include "DxLib.h"
#include <cmath>
#include <cstdlib>

Enemy::Enemy()
{
	// ìGÇÃèâä˙âª
	x = rand() % 450;
	y = 0;
	isDead = false;
	baseX = x;

	type = static_cast<EnemyType>(rand() % COUNT);

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
	
	if (y > 500)
	{
		isDead = true;
	}
}

void Enemy::Draw(int Image)
{
	DrawGraph(x, y, Image, TRUE);
}
