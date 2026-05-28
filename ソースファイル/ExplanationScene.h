#pragma once
#include "Scene.h"

class ExplanationScene : public Scene
{
private:

	// ”wŒi‰æ‘œ
	int bgImage;
	int playerImage;
	int enemyImage1;
	int enemyImage2;

	// ‰æ–ÊƒTƒCƒYæ“¾
	int screenW;
	int screenH;

public:
	ExplanationScene();
	~ExplanationScene();

	void Update()override;
	void Draw()override;
};

