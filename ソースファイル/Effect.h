#pragma once

class Effect
{
public:

	int x;
	int y;
	int image;

	int timer;

	bool isDead;

	Effect(int x, int y, int image);

	void Update();
	void Draw();
};

