#pragma once
#include "Scene.h"

class GameOverScene : public Scene
{
private:
	// “ü—ÍŠÇ—
	bool prevEnter;
	bool nowEnter;

public:
	void Update()override;
	void Draw()override;
};

