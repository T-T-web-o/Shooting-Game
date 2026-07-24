#include "GameScene.h"
#include "GameOverScene.h"
#include "GameManager.h"
#include "GameClearScene.h" 
#include "SoundManager.h"
#include "DxLib.h"

//============================================================
// 描画用定数
//============================================================

const int MAX_HP = 10;

const int BOSS_TIME_X = 360;  // ボス出現時間座標X
const int BOSS_TIME_Y = 0;    // ボス出現時間座標Y
const int BOSS_TEXT_X = 400;  // ボス関連テキストX

const int SCORE_X = 0;        // スコア座標X
const int SCORE_Y = 0;        // スコア座標Y

const int HP_BLOCK_WIDTH = 30;     // 黒いHPバーの幅
const int HP_BLOCK_HEIGHT = 20;    // 黒いHPバーの高さ

const int BG_SCROLL_SPEED = 2;     // 背景スクロール速度
const int BG_HEIGHT = 600;         // 背景画像の高さ

const int ENEMY_SPAWN_TIME = 60;   // 敵の出現間隔
const int BOSS_APPEAR_TIME = 1800; // ボス出現までの時間
const int CLEAR_WAIT_TIME = 60;    // ボス撃破後の待機時間

const int INVINCIBLE_TIME = 60;    // 無敵時間

const int NORMAL_SCORE = 100;   // 通常敵のスコア増減値
const int FAST_SCORE = 200;     // 高速敵のスコア増減値
const int ZIGZAG_SCORE = 300;   // ジグザグ敵のスコア増減値
const int BOSS_SCORE = 500;     // ボス撃破時のスコア

const int PAUSE_TEXT_X = 260;   // ボーズテキストX座標
const int PAUSE_TEXT_Y = 100;   // ポーズテキストY座標

const int PLAYER_ENEMY_HIT_DIV = 3;    // プレイヤーと敵の当たり判定縮小率
const int PLAYER_BOSS_HIT_DIV = 2;     // プレイヤーとボスの当たり判定縮小率
const int PLAYER_BOSS_HIT_OFFSET = 5;  // プレイヤーとボスの当たり判定補正値
const int BULLET_BOSS_HIT_DIV = 3;     // 弾とボスの当たり判定縮小率
const int BULLET_ENEMY_HIT_DIV = 2;    // 弾と敵の当たり判定縮小率

const int HP_BAR_X = 10;    // HPバーX座標
const int HP_BAR_Y = 450;   // HPバーY座標
const int CENTER_DIV = 2;   // 画像中央計算用
const int FPS = 60;   // 1秒あたりのフレーム数

// テキストカラー
const int COLOR_RED = GetColor(255, 0, 0);
const int COLOR_GREEN = GetColor(0, 255, 0);
const int COLOR_BLACK = GetColor(0, 0, 0);

// ポーズフォントサイズ
const int PAUSE_FONT_SIZE = 30;

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
	bossBulletImage1 = LoadGraph(TEXT("Resource/Model/bulletA.png"));
	bossBulletImage2 = LoadGraph(TEXT("Resource/Model/bulletB.png"));
	bossBulletImage3 = LoadGraph(TEXT("Resource/Model/bulletC.png"));

	// 敵画像
	enemyImage1 = LoadGraph(TEXT("Resource/Model/enemy1.png"));
	enemyImage2 = LoadGraph(TEXT("Resource/Model/enemy2.png"));
	enemyImage3 = LoadGraph(TEXT("Resource/Model/enemy3.png"));
	
	// 腐った敵画像
	rottenImage1 = LoadGraph(TEXT("Resource/model/rotten1.png"));
	rottenImage2 = LoadGraph(TEXT("Resource/model/rotten2.png"));
	rottenImage3 = LoadGraph(TEXT("Resource/model/rotten3.png"));

	// ボス画像
	bossImage = LoadGraph(TEXT("Resource/Model/boss.png"));

	// エフェクト画像
	effectImage1 = LoadGraph(TEXT("Resource/Model/effect1.png"));
	effectImage2 = LoadGraph(TEXT("Resource/Model/effect2.png"));
	effectImage3 = LoadGraph(TEXT("Resource/Model/effect3.png"));
	bossEffectImage = LoadGraph(TEXT("Resource/Model/bossEffect.png"));

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
	maxHP = MAX_HP;
	
	// ポーズ
	isPause = false;
	prevEsc = 0;

	// タイマー
	waitTimer = 0;
	isClear = false;

	// ボスの弾を撃つ間隔
	shotspan = 0;
}

//============================================================
// デストラクタ(使用した画像・効果音の解放)
//============================================================
GameScene::~GameScene()
{
	DeleteGraph(bgImage);
	DeleteGraph(playerImage);
	DeleteGraph(bulletImage);
	DeleteGraph(bossBulletImage1);
	DeleteGraph(bossBulletImage2);
	DeleteGraph(bossBulletImage3);
	DeleteGraph(enemyImage1);
	DeleteGraph(enemyImage3);
	DeleteGraph(enemyImage2);
	DeleteGraph(bossImage);
	DeleteGraph(effectImage1);
	DeleteGraph(effectImage2);
	DeleteGraph(effectImage3);
	DeleteGraph(bossEffectImage);
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
	bgY += BG_SCROLL_SPEED;

	if (bgY >= BG_HEIGHT)
	{
		bgY = 0;
	}

	// プレイヤーの更新
	player.Update();

	// 弾の更新
	UpdateBullet();

	// 敵の更新
	UpdateEnemy();

	// ボスの更新
	UpdateBoss();

	// エフェクトの更新
	UpdateEffect();

	// 敵を生成(ボス出現で削除)
    spawnTimer++;
	if (!isBoss && spawnTimer > ENEMY_SPAWN_TIME)
	{
		enemies.push_back(std::make_unique<Enemy>());
		spawnTimer = 0;
	}

	// 弾発射
	int nowSpace = CheckHitKey(KEY_INPUT_SPACE);

	if (nowSpace && !prevSpace)
	{ 
		// 弾発生時に効果音再生
		PlaySoundMem(SoundManager::shotSE, DX_PLAYTYPE_BACK);

		bullets.push_back(std::make_unique<Bullet>(player.x, player.y, 0, -10));
	}
	prevSpace = nowSpace;

	
	// 弾と敵の当たり判定
	CollisionBulletEnemy();

	// プレイヤーと敵の当たり判定
	CollisionPlayerEnemy();

	// Boss出現
	bossTimer++;

	if (!isBoss && bossTimer > BOSS_APPEAR_TIME)
	{
		isBoss = true;
		boss = std::make_unique<Boss>();
	}

	// Bosss出現中５秒ごとに弾発射
	if (boss)
	{
		shotspan++;
		if (shotspan % 180 == 0)
		{
			bossBullets.push_back(std::make_unique<Bullet>(boss->x, boss->y, 0, 10));
		}

		if (shotspan % 600 == 0)
		{
			bossBullets.push_back(std::make_unique<Bullet>(boss->x, boss->y, -3, 5));
			bossBullets.push_back(std::make_unique<Bullet>(boss->x, boss->y, 0, 5));
			bossBullets.push_back(std::make_unique<Bullet>(boss->x, boss->y, 3, 5));
		}
	}

	// 弾とボスの当たり判定
	CollisionBulletBoss();
	
	// プレイヤーとボスの当たり判定
	CollisionPlayerBoss();
	
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

	// 不要オブジェクトの削除
	RemoveDeadObjects();	
}

//============================================================
// 弾・敵・ボス・エフェクトの更新
//============================================================
void GameScene::UpdateBullet()
{
	for (auto& b : bullets)
	{
		b->Update();
	}

	for (auto& bb : bossBullets)
	{
		bb->Update();
	}
}

void GameScene::UpdateEnemy()
{
	
	for (auto& e : enemies)
	{
		e->Update();
	}
}

void GameScene::UpdateBoss()
{
	if (boss)
	{
		boss->Update();
	}
}

void GameScene::UpdateEffect()
{
	for (auto& ef : effects)
	{
		ef->Update();
	}
}

//============================================================
// 不要オブジェクトの削除
//============================================================
void GameScene::RemoveDeadObjects()
{
	// ===== 弾を削除 =====
	bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
		[](const std::unique_ptr<Bullet>& b)
		{
			return b->isDead;
		}),
		bullets.end());

	bossBullets.erase(std::remove_if(bossBullets.begin(), bossBullets.end(),
		[](const std::unique_ptr<Bullet>& bb)
		{
			return bb->isDead;
		}),
		bossBullets.end());

	// ===== 敵を削除 =====
	enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
		[](const std::unique_ptr<Enemy>& e)
		{
			return e->isDead;

		}),
		enemies.end());

	// ===== エフェクトを削除 =====
	effects.erase(std::remove_if(effects.begin(), effects.end(),
		[](const std::unique_ptr<Effect>& ef)
		{
			return ef->isDead;
		}),
		effects.end());
}

//============================================================
//  当たり判定
//============================================================
void GameScene::CollisionBulletEnemy()
{
	// 敵と弾の当たり判定
	for (auto& b : bullets)
	{
		for (auto& e : enemies)
		{
			// 当たり判定
			if (abs(b->x - e->x) < (bulletW + enemyW) / BULLET_ENEMY_HIT_DIV &&
				abs(b->y - e->y) < (bulletH + enemyH) / BULLET_ENEMY_HIT_DIV)
			{
				// 弾ヒット時に効果音再生
				PlaySoundMem(SoundManager::hitSE, DX_PLAYTYPE_BACK);

				b->isDead = true; // 弾削除
				e->hp -= b->damage;          // ダメージ

				// hpが0になったら削除
				if (e->hp <= 0)
				{
					// 腐っていたらスコアマイナス
					if (e->isRotten)
					{
						switch (e->type)
						{
						case NORMAL:
							score -= NORMAL_SCORE;
							break;
						case FAST:
							score -= FAST_SCORE;
							break;
						case ZIGZAG:
							score -= ZIGZAG_SCORE;
							break;
						}
					}
					// 腐ってなかったらスコアプラス
					else
					{
						switch (e->type)
						{
						case NORMAL:
							score += NORMAL_SCORE;
							break;
						case FAST:
							score += FAST_SCORE;
							break;
						case ZIGZAG:
							score += ZIGZAG_SCORE;
							break;
						}
					}
					e->isDead = true;

					int efImage = effectImage1;

					switch (e->type)
					{
					case NORMAL:
						efImage = effectImage1;
						break;
					case FAST:
						efImage = effectImage2;
						break;
					case ZIGZAG:
						efImage = effectImage3;
						break;
					}
					effects.push_back(std::make_unique<Effect>(e->x + enemyW / CENTER_DIV, e->y + enemyH / CENTER_DIV, efImage));
				}
				break;
			}
		}
	}
}

// 敵とプレイヤーの当たり判定
void GameScene::CollisionPlayerEnemy()
{
	for (auto& e : enemies)
	{
		if (abs(player.x - e->x) < (playerW + enemyW) / PLAYER_ENEMY_HIT_DIV &&
			abs(player.y - e->y) < (playerH + enemyH) / PLAYER_ENEMY_HIT_DIV)
		{
			if (player.InvincibilityTimer == 0)
			{
				e->isDead = true;
				player.hp--;
				player.InvincibilityTimer = INVINCIBLE_TIME;
				if (player.hp <= 0)
				{
					GameManager::GetInstance().ChangeScene(std::make_unique<GameOverScene>());
					return;
				}
			}
		}
	}
}

// ボスと弾の当たり判定
void GameScene::CollisionBulletBoss()
{
	if (boss)
	{
		for (auto& b : bullets)
		{
			if (abs(b->x - boss->x) < (bulletW + bossW) / BULLET_BOSS_HIT_DIV &&
				abs(b->y - boss->y) < (bulletH + bossH) / BULLET_BOSS_HIT_DIV)
			{
				// 弾ヒット時に効果音再生
				PlaySoundMem(SoundManager::hitSE, DX_PLAYTYPE_BACK);

				b->isDead = true; // 弾削除
				boss->hp -= b->damage;       // ダメージ
				// hpが0になったらクリア
				if (boss->hp <= 0)
				{
					score += BOSS_SCORE;

					effects.push_back(std::make_unique<Effect>(boss->x + bossW / CENTER_DIV, boss->y + bossH / CENTER_DIV, bossEffectImage));

					isClear = true;
					waitTimer = CLEAR_WAIT_TIME;
					boss->isDead = true;
					boss.reset();
				}
				break;
			}
		}
	}
}

// ボスとプレイヤーの当たり判定
void GameScene::CollisionPlayerBoss()
{
	if (boss)
	{
		if (abs(player.x - boss->x) < (playerW + bossW) / PLAYER_BOSS_HIT_DIV - PLAYER_BOSS_HIT_OFFSET &&
			abs(player.y - boss->y) < (playerH + bossH) / PLAYER_BOSS_HIT_DIV - PLAYER_BOSS_HIT_OFFSET)
		{
			if (player.InvincibilityTimer == 0)
			{
				player.hp--;
				player.InvincibilityTimer = INVINCIBLE_TIME;
				if (player.hp <= 0)
				{
					GameManager::GetInstance().ChangeScene(std::make_unique<GameOverScene>());
					return;
				}
			}
		}
	}
}

//============================================================
// ゲームの描画処理
//============================================================
void GameScene::Draw()
{
	// 背景画像描画(ループ)
	DrawGraph(0, bgY, bgImage, TRUE);
	DrawGraph(0, bgY - BG_HEIGHT, bgImage, TRUE);

	// プレイヤー画像
	player.Draw(playerImage);

	// 弾描画
	for (auto& b : bullets)
	{
		// 描画する画像を指定
		b->Draw(bulletImage);
	}
	for (auto& bb : bossBullets)
	{
		bb->Draw(bossBulletImage1);
	}

	// 敵描画
	for (auto& e : enemies)
	{
		int img = enemyImage1;

		// 種類ごとに描画する画像を指定
		if (e->isRotten)
		{
			switch (e->type)
			{
			case NORMAL:
				img = rottenImage1;
				break;
			case FAST:
				img = rottenImage2;
				break;
			case ZIGZAG:
				img = rottenImage3;
				break;
			}
		}
		else
		{
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
		}
		e->Draw(img);
	}

	// ボス描画
	if (boss&& !boss->isDead)
	{
		// 描画する画像を指定
		boss->Draw(bossImage);
	}

	// エフェクト描画
	for (auto& ef : effects)
	{
		ef->Draw();
	}

	// ボス出現までの時間を表示
	int remain = BOSS_APPEAR_TIME - bossTimer;
	if (remain > 0 && !isClear)
	{
		DrawFormatString(BOSS_TIME_X, BOSS_TIME_Y, COLOR_RED, TEXT("ボス出現まで: %d"), remain / FPS);
	}
	else if(remain<=0 && !isClear)
	{
		DrawString(BOSS_TEXT_X, BOSS_TIME_Y, TEXT("ボス出現中！"), COLOR_RED);
	}
	else
	{
		DrawString(BOSS_TEXT_X, BOSS_TIME_Y, TEXT("ボス撃破！"), COLOR_RED);
	}
	

	// 現在スコアを表示
	DrawFormatString(SCORE_X, SCORE_Y, COLOR_GREEN, TEXT("SCORE %d"), score);

	// プレイヤー体力表示
	int x = HP_BAR_X; int y = HP_BAR_Y; // 表示位置

	DrawBox(x, y, x + maxHP * HP_BLOCK_WIDTH, y + HP_BLOCK_HEIGHT, COLOR_BLACK, TRUE);
	for (int i = 0; i < player.hp; i++)
	{
		int r = 255 * (maxHP - i) / maxHP; // RGB値を計算
		int g = 255 * i / maxHP;
		int b = 0;
		DrawBox(x + 2 + i * 30, y + 2, x + 28 + i * 30, y+18, GetColor(r, g, b), TRUE);
	}

	// ポーズを表示
	SetFontSize(PAUSE_FONT_SIZE);
	if (isPause)
	{
		DrawString(PAUSE_TEXT_X, PAUSE_TEXT_Y, TEXT("PAUSE"), COLOR_RED);
	}
}
