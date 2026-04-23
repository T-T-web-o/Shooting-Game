#pragma once

enum EnemyType
{
	NORMAL,
	FAST,
	ZIGZAG,
	COUNT
};

class Enemy
{
private:
	int baseX;
public:
	int x, y;
	bool isDead;
	int hp;

	EnemyType type;

	Enemy();
	void Update();
	void Draw(int Image);
};

