#pragma once
#include "Scene.h"

class ClearScene : public Scene
{
public:
	// “ü—ÍŠÇ—
	bool prevEnter;
	bool nowEnter;

public:
	void Update()override;
	void Draw()override;
};

