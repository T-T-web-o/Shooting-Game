#pragma once

class Scene
{
public:
	virtual ~Scene() {}

	// XVˆ—
	virtual void Update() = 0;

	// •`‰æˆ—
	virtual void Draw() = 0;
};
