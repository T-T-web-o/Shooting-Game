#pragma once

class Effect
{
public:
	// 現在位置
	int x, y;

	// 使用する画像
	int image;

	// 描画時間
	int timer;

	// 削除フラグ
	bool isDead;

	// コンストラクタ(x座標、ｙ座標、使用する画像)
	Effect(int x, int y, int image);

	// 更新処理
	void Update();

	// 描画処理
	void Draw();
};

