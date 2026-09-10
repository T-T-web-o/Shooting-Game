#pragma once
#include "Player.h"

enum ItemType
{
	POWER,
	HP
};
class Item
{
public:
	int x, y;
	bool isDead;
	ItemType type;

	Item(int x, int y, ItemType type);
	void Update(Player&player);
	void Draw();
};

