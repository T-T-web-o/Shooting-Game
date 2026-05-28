#pragma once
#include "Scene.h"

class ResultScene:public Scene
{
private:

	// ”wŒi‰æ‘œ
	int bgImage;

	// ‰æ–ÊƒTƒCƒYæ“¾
	int screenW;
	int screenH;

	int score;
public:
	ResultScene();
	~ResultScene();

	void Update()override;
	void Draw()override;

};

