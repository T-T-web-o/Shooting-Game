#pragma once
class Player
{
public:
	// 現在位置
	int x, y;

	// コンストラクタ
	Player();

	// 更新処理
	void Update();

	// 描画処理
	void Draw(int Image);
};

