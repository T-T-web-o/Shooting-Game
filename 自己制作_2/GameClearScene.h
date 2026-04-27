#pragma once
#include "Scene.h"

class GameClearScene : public Scene
{
private:
	// 入力管理
	bool prevEnter;
	bool nowEnter;

	// 背景画像
	int bgImage;

	// 画面サイズ取得
	int screenW;
	int screenH;

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

