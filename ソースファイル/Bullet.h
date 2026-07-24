#pragma once
class Bullet
{
public:

	// 現在位置
	int x, y;

	// 弾の速度
	float vx, vy;

	// 弾のダメージ
	int damage;

	// 削除フラグ
	bool isDead;

	// コンストラクタ
	Bullet(int startX, int startY, float vx, float vy);

	// 更新処理
	void Update();

	// 描画処理
	void Draw(int Image);

};

