#pragma once
#include "Scene.h"

class TitleScene : public Scene
{
private:

	// “ü—ÍŠÇ—
	bool prevEnter;
	bool nowEnter;

	bool isReady;
public:
	TitleScene();
	void Update()override;
	void Draw()override;
};

