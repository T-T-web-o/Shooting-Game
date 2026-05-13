#include "GameScene.h"
#include "GameOverScene.h"
#include "GameManager.h"
#include "GameClearScene.h" 
#include "SoundManager.h"
#include "DxLib.h"

//============================================================
// 描画用定数
//============================================================

// ボス関連
const int BOSS_TIME_X = 360;
const int BOSS_TIME_Y = 0;
const int BOSS_TEXT_X = 400;

// スコア
const int SCORE_X = 0;
const int SCORE_Y = 0;

// HPバー
const int HP_BLOCK_WIDTH = 30;       // 黒いHPバーの幅
const int HP_BLOCK_HEIGHT = 20;      // 黒いHPバーの高さ


//============================================================
// コンストラクタ
//============================================================
GameScene::GameScene()
{
	// 背景画像のY座標
	bgY = 0;

	// 背景画像
	bgImage = LoadGraph(TEXT("Resource/Model/background.png"));

	// プレイヤー画像
	playerImage = LoadGraph(TEXT("Resource/Model/player.png"));

	// 弾画像
	bulletImage = LoadGraph(TEXT("Resource/Model/bullet.png"));

	// 敵画像
	enemyImage1 = LoadGraph(TEXT("Resource/Model/enemy1.png"));
	enemyImage2 = LoadGraph(TEXT("Resource/Model/enemy2.png"));
	enemyImage3 = LoadGraph(TEXT("Resource/Model/enemy3.png"));
	
	// ボス画像
	bossImage = LoadGraph(TEXT("Resource/Model/boss.png"));

	// 画像サイズ取得
	GetGraphSize(playerImage, &playerW, &playerH);
	GetGraphSize(enemyImage1, &enemyW, &enemyH);
	GetGraphSize(bulletImage, &bulletW, &bulletH);
	GetGraphSize(bossImage, &bossW, &bossH);
	
	// 画面サイズ取得
	GetDrawScreenSize(&screenW, &screenH);

	// ゲーム状態
	bossTimer = 0;

	// 入力・生成管理
	prevSpace = 0;
	spawnTimer = 0;

	// ボス出現フラグ
	isBoss = false;

	// UI
	score = 0;
	maxHP = 10;
	
	// ポーズ
	isPause = false;
	prevEsc = 0;

	// タイマー
	waitTimer = 0;
	isClear = false;
}

//============================================================
// デストラクタ(使用した画像・効果音の解放)
//============================================================
GameScene::~GameScene()
{
	DeleteGraph(bgImage);
	DeleteGraph(playerImage);
	DeleteGraph(bulletImage);
	DeleteGraph(enemyImage1);
	DeleteGraph(enemyImage3);
	DeleteGraph(enemyImage2);
	DeleteGraph(bossImage);
}

//============================================================
// ゲームの更新処理
//============================================================
void GameScene::Update()
{
	// Escでポーズ
	int nowEsc = CheckHitKey(KEY_INPUT_ESCAPE);
	if (nowEsc && !prevEsc)
	{
		isPause = !isPause;
	}
	prevEsc = nowEsc;


	if (isPause)
	{
		return;
	}

	// 背景スクロール速度
	bgY += 2; 

	if (bgY >= 600)
	{
		bgY = 0;
	}


	// プレイヤーの更新
	player.Update();

	// ボス撃破
	if (isClear)
	{
		waitTimer--;

		if (waitTimer <= 0)
		{
			// クリアシーンへ移行
			GameManager::GetInstance().SetScore(score);
			GameManager::GetInstance().ChangeScene(std::make_unique<GameClearScene>());
			return;
		}
	}

	// 弾発射
	int nowSpace = CheckHitKey(KEY_INPUT_SPACE);

	if (nowSpace && !prevSpace)
	{ 
		// 弾発生時に効果音再生
		PlaySoundMem(SoundManager::shotSE, DX_PLAYTYPE_BACK);

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

	// 敵を生成(ボス出現で削除)
	spawnTimer++;
	if (!isBoss && spawnTimer > 60)
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
			if (abs(b->x - e->x) < (bulletW + enemyW) / 2 && 
				abs(b->y - e->y) < (bulletH + enemyH) / 2)
			{
				// 弾ヒット時に効果音再生
				PlaySoundMem(SoundManager::hitSE, DX_PLAYTYPE_BACK);

				b->isDead = true; // 弾削除
				e->hp -= b->damage;          // ダメージ

				// hpが0になったら削除
				if (e->hp <= 0)
				{
					switch (e->type)
					{
					case NORMAL:
						score += 100;
						break;
					case FAST:
						score += 200;
						break;
					case ZIGZAG:
						score += 300;
						break;
					}
					e->isDead = true;
				}
				break;
			}
		}
	}

	// 敵とプレイヤーの当たり判定
	for (auto& e : enemies)
	{
		if (abs(player.x - e->x) < (playerW + enemyW) / 3 &&
			abs(player.y - e->y) < (playerH + enemyH) / 3)
		{
			if (player.InvincibilityTimer == 0)
			{
				e->isDead = true;
				player.hp--;
				player.InvincibilityTimer = 60;
				if (player.hp <= 0)
				{
					GameManager::GetInstance().ChangeScene(std::make_unique<GameOverScene>());
					return;
				}
			}
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
			if (abs(b->x - boss->x) < (bulletW + bossW) / 3 &&
				abs(b->y - boss->y) < (bulletH + bossH) / 3)
			{
				// 弾ヒット時に効果音再生
				PlaySoundMem(SoundManager::hitSE, DX_PLAYTYPE_BACK);

				b->isDead = true; // 弾削除
				boss->hp -= b->damage;       // ダメージ
				// hpが0になったらクリア
				if (boss->hp <= 0)
				{
					score += 500;
					isClear = true;
					waitTimer = 180;
					boss->isDead = true;
					boss.reset();
				}
				break;
			}
		}
	}

	// ボスとプレイヤーの当たり判定
	if (boss)
	{
		if (abs(player.x - boss->x) < (playerW + bossW) / 2 - 5 && 
			abs(player.y - boss->y) < (playerH + bossH) / 2 - 5)
		{
			if (player.InvincibilityTimer == 0)
			{
				player.hp--;
				player.InvincibilityTimer = 60;
				if (player.hp <= 0)
				{
					GameManager::GetInstance().ChangeScene(std::make_unique<GameOverScene>());
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

//============================================================
// ゲームの描画処理
//============================================================
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
		// 描画する画像を指定
		b->Draw(bulletImage);
	}

	// 敵描画
	for (auto& e : enemies)
	{
		int img = enemyImage1;

		// 種類ごとに描画する画像を指定
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
	if (boss&& !boss->isDead)
	{
		// 描画する画像を指定
		boss->Draw(bossImage);
	}

	// ボス出現までの時間を表示
	int remain = 1800 - bossTimer;
	if (remain > 0 && !isClear)
	{
		DrawFormatString(BOSS_TIME_X, BOSS_TIME_Y, GetColor(255, 0, 0), TEXT("ボス出現まで: %d"), remain / 60);
	}
	else if(remain<=0 && !isClear)
	{
		DrawString(BOSS_TEXT_X, BOSS_TIME_Y, TEXT("ボス出現中！"), GetColor(255, 0, 0));
	}
	else
	{
		DrawString(BOSS_TEXT_X, BOSS_TIME_Y, TEXT("ボス撃破！"), GetColor(255, 0, 0));
	}
	

	// 現在スコアを表示
	DrawFormatString(SCORE_X, SCORE_Y, GetColor(0, 255, 0), TEXT("SCORE %d"), score);

	// プレイヤー体力表示
	int x = 10; int y = 450; // 表示位置

	DrawBox(x, y, x + maxHP * HP_BLOCK_WIDTH, y + HP_BLOCK_HEIGHT, GetColor(0,0,0), TRUE);
	for (int i = 0; i < player.hp; i++)
	{
		int r = 255 * (maxHP - i) / maxHP; // RGB値を計算
		int g = 255 * i / maxHP;
		int b = 0;
		DrawBox(x + 2 + i * 30, y + 2, x + 28 + i * 30, y+18, GetColor(r, g, b), TRUE);
	}

	// ポーズを表示
	SetFontSize(30);
	if (isPause)
	{
		DrawString(260, 100, TEXT("PAUSE"), GetColor(255, 0, 0));
	}
}
