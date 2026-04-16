#pragma once
class Enemy
{
public:
	int x, y;
	bool Dead;

	Enemy();

	void Update();
	void Draw();
};

