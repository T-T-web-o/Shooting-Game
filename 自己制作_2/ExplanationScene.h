#pragma once
#include "Scene.h"

class ExplanationScene : public Scene
{
private:
	// “ü—ÍŠÇ—
	bool prevEnter;
	bool nowEnter;

	// ”wŒi‰æ‘œ
	int bgImage;
	int playerImage;
	int enemyImage1;
	int enemyImage2;

	// ‰æ–ÊƒTƒCƒYæ“¾
	int screenW;
	int screenH;

	int page;
public:
	ExplanationScene();
	~ExplanationScene();

	void Update()override;
	void Draw()override;
};

