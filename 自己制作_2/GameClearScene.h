#pragma once
#include "Scene.h"

class GameClearScene : public Scene
{
public:
	// 入力管理
	bool prevEnter;
	bool nowEnter;

	// 背景画像
	int bgImage;

public:
	// コンストラクタ
	GameClearScene();

	// デストラクタ
	~GameClearScene();

	// 更新処理
	void Update()override;

    // 描画処理
	void Draw()override;
};

