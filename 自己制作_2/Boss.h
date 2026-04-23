#pragma once
class Boss
{
public:
	int x, y;
	int hp;
	bool isDead;

	Boss();

	void Update();
	void Draw(int Image);
};

