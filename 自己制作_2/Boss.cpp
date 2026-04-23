#include "Boss.h"
#include "DxLib.h"
#include <cmath>

Boss::Boss()
{
	x = 200;
	y = 50;
	hp = 30;
	isDead = false;
}

void Boss::Update()
{
	x = 200 + static_cast<int>(sin(y * 0.05) * 100);
	y += 1;
}

void Boss::Draw(int Image)
{
	DrawGraph(x, y, Image, TRUE);
}
