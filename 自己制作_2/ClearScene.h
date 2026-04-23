#pragma once
#include "Scene.h"

class ClearScene : public Scene
{
public:
	// “ü—ÍŠÇ—
	bool prevEnter;
	bool nowEnter;

public:

	// XVˆ—
	void Update()override;

   // •`‰æˆ—
	void Draw()override;
};

