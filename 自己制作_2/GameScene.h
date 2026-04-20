#pragma once
#include "Scene.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include <vector>
#include <memory>

class GameScene : public Scene
{
private:
	Player player;

	std::vector<std::unique_ptr<Bullet>>bullets;
	std::vector<std::unique_ptr<Enemy>>enemies;

	// ‰æ‘œ
	int bgY;
	int bgImage;
	int bulletImage;
	int playerImage;
	int enemyImage;

	int clearTimer;
	bool isClear;

public:
	~GameScene();
	GameScene();
	void Update() override;
	void Draw() override;
};

