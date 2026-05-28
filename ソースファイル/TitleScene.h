#pragma once
#include "Scene.h"

class TitleScene : public Scene
{
private:

	// タイトル画像
	int titleImage;

	// SE
	int titleSE;

	// シーン切り替え時のバグ防止
	bool isReady;

	// 画面サイズ取得
	int screenW;
	int screenH;


public:

	// コンストラクタ
	TitleScene();

	// デストラクタ
	~TitleScene();

	// 更新処理
	void Update()override;

	// 描画処理
	void Draw()override;
};

