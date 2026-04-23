#pragma once
class Bullet
{
private:

public:

	// 現在位置
	int x, y;

	// 削除フラグ
	bool isDead;

	// コンストラクタ
	Bullet(int startX, int startY);

	// 更新処理
	void Update();

	// 描画処理
	void Draw(int Image);

};

