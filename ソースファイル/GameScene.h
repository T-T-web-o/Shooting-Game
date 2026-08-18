#pragma once
#include "Scene.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Boss.h"
#include "Effect.h"
#include <vector>
#include <memory>

class GameScene : public Scene
{
private:
	// プレイヤー
	Player player;

	// 弾・敵・ボスの管理
	std::vector<std::unique_ptr<Bullet>>bullets;
	std::vector<std::unique_ptr<Bullet>>bossBullets;
	std::vector<std::unique_ptr<Enemy>>enemies;
	std::unique_ptr<Boss>boss;
	std::vector<std::unique_ptr<Effect>>effects;

	// ボス出現フラグ
	bool isBoss;

	// 更新処理
	void UpdateBullet();
	void UpdateEnemy();
	void UpdateBoss();
	void UpdateEffect();

	// 削除処理
	void RemoveDeadObjects();

	// 当たり判定
	void CollisionBulletEnemy();
	void CollisionPlayerEnemy();
	void CollisionBulletBoss();
	void CollisionPlayerBoss();
	void CollisionBossBulletPlayer();

	// 画像
	int bgY; // 背景のスクロール位置
	int bgImage;
	int bulletImage;
	int bossBulletImage1;
	int bossBulletImage2;
	int bossBulletImage3;
	int playerImage;
	int enemyImage1;
	int enemyImage2;
	int enemyImage3;
	int rottenImage1;
	int rottenImage2;
	int rottenImage3;
	int bossImage;
	int effectImage1;
	int effectImage2;
	int effectImage3;
	int bossEffectImage;

	// 画像サイズ
	int playerW, playerH;
	int enemyW, enemyH;
	int bulletW, bulletH;
	int bossW, bossH;
	int effectW, effectH;

	// 画面サイズ取得
	int screenW;
	int screenH;

	// ゲーム状態
	int bossTimer;

	// 入力・生成の管理
	int prevSpace;
	int spawnTimer;
	
	// UI
	int score;
	int maxHP;
	int hpWidth;

	// ポーズ
	bool isPause;
	int prevEsc;

	// Boss撃破
	int waitTimer;
	bool isClear;

	// Bossの球を撃つ間隔
	int shotspan;

	// ゲームオーバー
	bool isGameOver;

public:

	~GameScene();
	GameScene();

	// 更新処理
	void Update() override;

	// 描画処理
	void Draw() override;
};

