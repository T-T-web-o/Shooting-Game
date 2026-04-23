#include "GameScene.h"
#include "GameOverScene.h"
#include "GameManager.h"
#include "ClearScene.h" 
#include "DxLib.h"


GameScene::GameScene()
{
	// 背景画像のY座標
	bgY = 0;

	// 背景画像
	bgImage = LoadGraph(TEXT("Resource/background.png"));

	// プレイヤー画像
	playerImage = LoadGraph(TEXT("Resource/player.png"));

	// 弾画像
	bulletImage = LoadGraph(TEXT("Resource/bullet.png"));

	// 敵画像
	enemyImage1 = LoadGraph(TEXT("Resource/enemy1.png"));
	enemyImage2 = LoadGraph(TEXT("Resource/enemy2.png"));
	enemyImage3 = LoadGraph(TEXT("Resource/enemy3.png"));
	
	// ボス画像
	bossImage = LoadGraph(TEXT("Resource/boss.png"));

	// 画像サイズ取得
	GetGraphSize(playerImage, &playerW, &playerH);
	GetGraphSize(enemyImage1, &enemyW, &enemyH);
	GetGraphSize(bulletImage, &bulletW, &bulletH);
	GetGraphSize(bossImage, &bossW, &bossH);
	
	// ゲーム状態
	bossTimer = 0;

	// 入力・生成管理
	prevSpace = 0;
	spawnTimer = 0;

	isBoss = false;
}


GameScene::~GameScene()
{
	// 画像の解放
	DeleteGraph(bgImage);
	DeleteGraph(playerImage);
	DeleteGraph(bulletImage);
	DeleteGraph(enemyImage1);
	DeleteGraph(enemyImage3);
	DeleteGraph(enemyImage2);
	DeleteGraph(bossImage);
}

void GameScene::Update()
{

	// 背景スクロール速度
	bgY += 2; 

	if (bgY >= 600)
	{
		bgY = 0;
	}

	// プレイヤーの更新
	player.Update();

	// 弾発射
	int nowSpace = CheckHitKey(KEY_INPUT_SPACE);

	if (nowSpace && !prevSpace)
	{
		bullets.push_back(std::make_unique<Bullet>(player.x, player.y));
	}
	prevSpace = nowSpace;

	// 弾更新
	for (auto& b : bullets)
	{
		b->Update();
	}

	// 敵更新
	for (auto& e : enemies)
	{
		e->Update();
	}

	// ボス更新
	if (boss)
	{
		boss->Update();
	}


	// 敵を生成
	spawnTimer++;
	if (spawnTimer > 120) 
	{
		enemies.push_back(std::make_unique<Enemy>());
		spawnTimer = 0;
	}

	// 敵と弾の当たり判定
	for (auto& b : bullets)
	{
		for (auto& e : enemies)
		{
			// 当たり判定
			if (abs(b->x - e->x) < (bulletW + enemyW) / 2 && abs(b->y - e->y) < (bulletH + enemyH) / 2)
			{
				b->isDead = true; // 弾削除
				e->hp--;          // ダメージ

				// hpが0になったら削除
				if (e->hp <= 0)
				{
					e->isDead = true;
				}
				break;
			}
		}
	}

	// 敵とプレイヤーの当たり判定
	for (auto& e : enemies)
	{
		if (abs(player.x - e->x) < (playerW + enemyW) / 2-5 &&abs(player.y - e->y) < (playerH + enemyH) / 2-5)
		{
			GameManager::GetInstance().ChangeScene(std::make_unique<GameOverScene>());
			return;
		}
	}

	// Boss出現
	bossTimer++;

	if (!isBoss && bossTimer > 1800)
	{
		isBoss = true;
		boss = std::make_unique<Boss>();
	}

	// ボスと弾の当たり判定
	if (boss)
	{
		for (auto& b : bullets)
		{
			if (abs(b->x - boss->x) < (bulletW + bossW) / 2 - 5 && abs(b->y - boss->y) < (bulletH + bossH) / 2 - 5)
			{
				b->isDead = true; // 弾削除
				boss->hp--;       // ダメージ

				// hpが0になったらクリア
				if (boss->hp <= 0)
				{
					// クリアシーンへ移行
					GameManager::GetInstance().ChangeScene(std::make_unique<ClearScene>());
					return;
				}
			}
		}
	}


	// ===== 弾を削除 =====
	bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
		[](const std::unique_ptr<Bullet>& b)
		{
			return b->isDead;
		}),
		bullets.end());

	// ===== 敵を削除 =====
	enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
		[](const std::unique_ptr<Enemy>& e)
		{
			return e->isDead;

		}),
		enemies.end());

}

void GameScene::Draw()
{
	// 背景画像描画(ループ)
	DrawGraph(0, bgY, bgImage, TRUE);
	DrawGraph(0, bgY - 600, bgImage, TRUE);

	// プレイヤー画像
	player.Draw(playerImage);

	// 弾描画
	for (auto& b : bullets)
	{
		b->Draw(bulletImage);
	}

	// 敵描画
	for (auto& e : enemies)
	{
		int img = enemyImage1;

		// 種類ごとに画像を変更
		switch (e->type)
		{
		case NORMAL:
			img = enemyImage1;
			break;
		case FAST:
			img = enemyImage2;
			break;
		case ZIGZAG:
			img = enemyImage3;
			break;
		}
		e->Draw(img);
	}

	// ボス描画
	if (boss)
	{
		boss->Draw(bossImage);
	}
}
