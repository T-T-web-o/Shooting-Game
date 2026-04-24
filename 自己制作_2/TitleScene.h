#pragma once
#include "Scene.h"

class TitleScene : public Scene
{
private:

	// 入力管理
	bool prevEnter;
	bool nowEnter;
	
	// タイトル画像
	int titleImage;

	// シーン切り替え時のバグ防止
	bool isReady;
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

