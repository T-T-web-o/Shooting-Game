#include "GameScene.h"
#include "GameOverScene.h"
#include "GameManager.h"
#include "ClearScene.h" 
#include "DxLib.h"


GameScene::GameScene()
{
	bgY = 0;
	bgImage = LoadGraph(TEXT("Resource/background.png"));
	playerImage = LoadGraph(TEXT("Resource/player.png"));
	bulletImage = LoadGraph(TEXT("Resource/bullet.png"));
	enemyImage1 = LoadGraph(TEXT("Resource/enemy1.png"));
	enemyImage2 = LoadGraph(TEXT("Resource/enemy2.png"));
	enemyImage3 = LoadGraph(TEXT("Resource/enemy3.png"));
	
	GetGraphSize(playerImage, &playerW, &playerH);
	GetGraphSize(enemyImage1, &enemyW, &enemyH);
	GetGraphSize(bulletImage, &bulletW, &bulletH);

	clearTimer = 0;
	isClear = false;

	prevSpace = 0;
	spawnTimer = 0;
}


GameScene::~GameScene()
{
	DeleteGraph(bgImage);
	DeleteGraph(playerImage);
	DeleteGraph(bulletImage);
	DeleteGraph(enemyImage1);
	DeleteGraph(enemyImage3);
	DeleteGraph(enemyImage2);
}


void GameScene::Update()
{

	// ƒXƒNƒ[ƒ‹‘¬“x
	bgY += 2; 

	if (bgY >= 600)
	{
		bgY = 0;
	}

	// ƒvƒŒƒCƒ„[‚ÌXV
	player.Update();

	// ’e”­Ë
	int nowSpace = CheckHitKey(KEY_INPUT_SPACE);

	if (nowSpace && !prevSpace)
	{
		bullets.push_back(std::make_unique<Bullet>(player.x, player.y));
	}
	prevSpace = nowSpace;

	// ’eXV
	for (auto& b : bullets)
	{
		b->Update();
	}

	// “GXV
	for (auto& e : enemies)
	{
		e->Update();
	}

	// “G‚ğ¶¬
	spawnTimer++;
	if (spawnTimer > 120) 
	{
		enemies.push_back(std::make_unique<Enemy>());
		spawnTimer = 0;
	}

	

	// “G‚Æ’e‚Ì“–‚½‚è”»’è
	for (auto& b : bullets)
	{
		for (auto& e : enemies)
		{
			if (abs(b->x - e->x) < (bulletW + enemyW) / 2 && abs(b->y - e->y) < (bulletH + enemyH) / 2)
			{
				b->isDead = true;
				e->hp--;

				if (e->hp <= 0)
				{
					e->isDead = true;
				}
				break;
			}
		}
	}

	// “G‚ÆƒvƒŒƒCƒ„[‚Ì“–‚½‚è”»’è
	for (auto& e : enemies)
	{
		if (abs(player.x - e->x) < (playerW + enemyW) / 2-5 &&abs(player.y - e->y) < (playerH + enemyH) / 2-5)
		{
			GameManager::GetInstance().ChangeScene(std::make_unique<GameOverScene>());
			return;
		}
	}

	// ===== ’e‚ğíœ =====
	bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
		[](const std::unique_ptr<Bullet>& b)
		{
			return b->isDead;
		}),
		bullets.end());

	// ===== “G‚ğíœ =====
	enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
		[](const std::unique_ptr<Enemy>& e)
		{
			return e->isDead;

		}),
		enemies.end());

	// ƒQ[ƒ€ƒNƒŠƒA
	clearTimer++;

	if (clearTimer > 1800) 
	{
		isClear = true;
	}

	if (isClear)
	{
		GameManager::GetInstance().ChangeScene(std::make_unique<ClearScene>());
		return;
	}
}

void GameScene::Draw()
{
	DrawGraph(0, bgY, bgImage, TRUE);
	DrawGraph(0, bgY - 600, bgImage, TRUE);

	player.Draw(playerImage);

	// ’e•`‰æ
	for (auto& b : bullets)
	{
		b->Draw(bulletImage);
	}

	// “G•`‰æ
	for (auto& e : enemies)
	{
		int img = enemyImage1;

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
}
