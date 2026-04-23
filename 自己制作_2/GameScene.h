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
	// プレイヤー
	Player player;

	// 弾・敵の管理
	std::vector<std::unique_ptr<Bullet>>bullets;
	std::vector<std::unique_ptr<Enemy>>enemies;

	// 画像
	int bgY; // 背景のスクロール位置
	int bgImage;
	int bulletImage;
	int playerImage;
	int enemyImage1;
	int enemyImage2;
	int enemyImage3;

	// 画像サイズ
	int playerW, playerH;
	int enemyW, enemyH;
	int bulletW, bulletH;

	// ゲーム状態
	int clearTimer;
	bool isClear;

	// 入力・生成の管理
	int prevSpace;
	int spawnTimer;
	
public:

	~GameScene();
	GameScene();

	// 更新処理
	void Update() override;

	// 描画処理
	void Draw() override;
};

