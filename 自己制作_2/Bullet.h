#pragma once
class Bullet
{
public:
	int x, y;
	bool Dead;

	Bullet(int x, int y);

	void Update();
	void Draw();

};

