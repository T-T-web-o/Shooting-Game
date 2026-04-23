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
	int enemyImage1;
	int enemyImage2;
	int enemyImage3;

	// ‰æ‘œƒTƒCƒY
	int playerW, playerH;
	int enemyW, enemyH;
	int bulletW, bulletH;

	int clearTimer;
	bool isClear;

	int prevSpace;
	int spawnTimer;
	
public:
	~GameScene();
	GameScene();
	void Update() override;
	void Draw() override;
};

