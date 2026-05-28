#include "Input.h"
#include "DxLib.h"

//staticメンバ変数
int Input::nowEnter = 0;
int Input::prevEnter = 0;

void Input::Update()
{
	// 前フレームの値を保存
	prevEnter = nowEnter;

	// 今の入力を保存
	nowEnter = CheckHitKey(KEY_INPUT_RETURN);
}

bool Input::IsTriggerEnter()
{
	return nowEnter && !prevEnter;
}
