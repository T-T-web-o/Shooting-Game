#include "Boss.h"
#include "DxLib.h"
#include <cmath>

Boss::Boss()
{
	x = 200;
	y = 50;
	hp = 30;
	isDead = false;
	t = 0;
}

void Boss::Update()
{
	t++;
	x = 200 + static_cast<int>(sin(t * 0.05) * 100);
	
}

void Boss::Draw(int Image)
{
	DrawGraph(x, y, Image, TRUE);
}
