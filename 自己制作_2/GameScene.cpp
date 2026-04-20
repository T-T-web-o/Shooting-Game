#include "GameScene.h"
#include "GameOverScene.h"
#include "GameManager.h"
#include "DxLib.h"


GameScene::GameScene()
{
	bgY = 0;
	bgImage = LoadGraph(TEXT("Resource/background.png"));
	playerImage = LoadGraph(TEXT("Resource/player.png"));
	bulletImage = LoadGraph(TEXT("Resource/bullet.png"));
	enemyImage = LoadGraph(TEXT("Resource/enemy.png"));
	
}


GameScene::~GameScene()
{
	DeleteGraph(bgImage);
	DeleteGraph(playerImage);
	DeleteGraph(bulletImage);
	DeleteGraph(enemyImage);
}


void GameScene::Update()
{
	static int prevSpace = 0;

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
	if (rand() % 60 == 0)
	{
		enemies.push_back(std::make_unique<Enemy>());
	}

	// “G‚Æ’e‚Ì“–‚½‚è”»’è
	for (auto& b : bullets)
	{
		for (auto& e : enemies)
		{
			if (abs(b->x - e->x) < 20 && abs(b->y - e->y) < 20)
			{
				b->Dead = true;
				e->Dead = true;
			}
		}
	}

	// “G‚ÆƒvƒŒƒCƒ„[‚Ì“–‚½‚è”»’è
	for (auto& e : enemies)
	{
		if (abs(player.x - e->x) < 30 &&abs(player.y - e->y) < 25)
		{
			GameManager::GetInstance().ChangeScene(std::make_unique<GameOverScene>());
			return;
		}
	}

	// ===== ’e‚ğíœ =====
	bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
		[](const std::unique_ptr<Bullet>& b)
		{
			return b->Dead;
		}),
		bullets.end());

	// ===== “G‚ğíœ =====
	enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
		[](const std::unique_ptr<Enemy>& e)
		{
			return e->Dead;
		}),
		enemies.end());
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
		e->Draw(enemyImage);
	}
}
