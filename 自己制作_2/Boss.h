#pragma once
class Boss
{
private:
	int t;
public:
	int x, y;
	int hp;
	bool isDead;

	Boss();

	void Update();
	void Draw(int Image);
};

