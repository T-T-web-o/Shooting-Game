#pragma once
#include "Scene.h"
#include <memory>

class GameManager
{
private:
	std::unique_ptr<Scene> currentScene;

	GameManager();
	
public:
	static GameManager& GetInstance();

	void Update();
	void Draw();

	void ChangeScene(std::unique_ptr<Scene>next);
};

