#pragma once
class Bullet
{
private:

public:
	int x, y;
	bool isDead;

	Bullet(int startX, int startY);

	~Bullet();
	void Update();
	void Draw(int Image);

};

