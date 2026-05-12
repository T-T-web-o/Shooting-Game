#pragma once
class Boss
{
private:
	// 移動用タイマー
	int t;
public:
	int x, y;    // 現在位置
	int hp;      // 体力
	bool isDead; // 削除フラグ

	// コンストラクタ
	Boss();

	// 更新処理
	void Update();

	// 描画処理
	void Draw(int Image);
};

