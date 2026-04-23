#pragma once
#include "Scene.h"

class GameOverScene : public Scene
{
private:
	// 入力管理
	bool prevEnter;
	bool nowEnter;

	// 背景画像
	int bgImage;

public:
	// コンストラクタ
	GameOverScene();

	// デストラクタ
	~GameOverScene();

	// 更新処理
	void Update()override;

	// 描画処理
	void Draw()override;
};

