#pragma once
class Bullet
{
public:
	int x, y;
	bool Dead;

	Bullet(int startX, int startY);

	void Update();
	void Draw();

};

