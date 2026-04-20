#include "GameManager.h"
#include "GameScene.h"
#include "TitleScene.h"

// コンストラクタ
GameManager::GameManager()
{
    currentScene = std::make_unique<TitleScene>();
}

// GameManagerのインスタンス取得（シングルトン）
GameManager& GameManager::GetInstance()
{
    static GameManager instance;
    return instance;
}

// 更新処理
void GameManager::Update()
{
    currentScene->Update();
}

// 描画処理
void GameManager::Draw()
{
    currentScene->Draw();
}

// シーン切り替え処理
void GameManager::ChangeScene(std::unique_ptr<Scene> next)
{
    currentScene = std::move(next);
}
