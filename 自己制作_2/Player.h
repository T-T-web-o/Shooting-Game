#pragma once
class Player
{
public:
	// 現在位置
	int x, y;

	// 現在の体力
	int hp;

	// 無敵時間
	int InvincibilityTimer;

	// コンストラクタ
	Player();

	// 更新処理
	void Update();

	// 描画処理
	void Draw(int Image);
};

