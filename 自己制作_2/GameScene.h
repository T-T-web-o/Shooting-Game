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

public:
	void Update() override;
	void Draw() override;
};

