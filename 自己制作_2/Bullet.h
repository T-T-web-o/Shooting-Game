#pragma once
class Bullet
{
private:

public:
	int x, y;
	bool Dead;

	Bullet(int startX, int startY);

	~Bullet();
	void Update();
	void Draw(int Image);

};

