#pragma once
#include "Scene.h"
#include <memory>

class GameManager
{
private:
	// 現在進行中のシーン
	std::unique_ptr<Scene> currentScene;

	// コンストラクタ
	GameManager();
	
public:

	// GameManagerのインスタンス取得
	static GameManager& GetInstance();

	// 更新処理
	void Update();
	// 描画処理
	void Draw();

	// シーンの切り替え
	void ChangeScene(std::unique_ptr<Scene>next);
};

