#include "SoundManager.h"
#include "DxLib.h"

//============================================================
// 静的メンバ変数定義
// 各SEのハンドルを保持する
//============================================================
int SoundManager::titleSE;
int SoundManager::shotSE;
int SoundManager::hitSE;

void SoundManager::Load()
{
	// 効果音読み込み
	titleSE = LoadSoundMem(TEXT("Resource/bgm/title.mp3"));
	shotSE = LoadSoundMem(TEXT("Resource/bgm/shot.wav"));
	hitSE = LoadSoundMem(TEXT("Resource/bgm/hit.wav"));
}

void SoundManager::Release()
{
	DeleteSoundMem(titleSE);
	DeleteSoundMem(shotSE);
	DeleteSoundMem(hitSE);
}
