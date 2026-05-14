#include "Effect.h"
#include "DxLib.h"


Effect::Effect(int x, int y ,int image)
{
	this->x = x;
	this->y = y;
	this->image = image;

	timer = 10;

	isDead = false;

	
}

void Effect::Update()
{
	timer--;

	if (timer <= 0)
	{
		isDead = true;
	}
}

void Effect::Draw()
{
	int w, h;
	GetGraphSize(image, &w, &h);

	DrawGraph(x - w / 2, y - h / 2, image, TRUE);
}
