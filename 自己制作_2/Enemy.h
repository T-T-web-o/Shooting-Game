#pragma once

// 敵の種類
enum EnemyType
{
	NORMAL,
	FAST,
	ZIGZAG,
	COUNT
};


class Enemy
{
private:

	// ZIGZAG移動のｘ座標
	int baseX;

public:
	int x, y;     // 現在位置
	bool isDead;  // 削除フラグ
	int hp;       // 体力

	// 敵の種類
	EnemyType type;

	// コンストラクタ　
	Enemy();

	// 更新処理
	void Update();
	
	// 描画処理
	void Draw(int Image);
};

