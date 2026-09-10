#pragma once
class Bullet
{
public:

	// 現在位置
	int x, y;

	// 弾の速度
	float vx, vy;

	// 削除フラグ
	bool isDead;

	// 弾のダメージ
	int damage;

	// コンストラクタ
	Bullet(int startX, int startY, float vx, float vy,int image,int damage);

	// 画像
	int image;

	// 更新処理
	void Update();

	// 描画処理
	void Draw();

};

