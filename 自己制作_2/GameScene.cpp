#include "GameScene.h"
#include "DxLib.h"

void GameScene::Update()
{
	static int prevSpace = 0;

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

	// “–‚½‚è”»’è
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
	player.Draw();

	// ’e•`‰æ
	for (auto& b : bullets)
	{
		b->Draw();
	}

	// “G•`‰æ
	for (auto& e : enemies)
	{
		e->Draw();
	}
}
