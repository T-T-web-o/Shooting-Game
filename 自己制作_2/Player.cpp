#include "Player.h"
#include "DxLib.h"

Player::Player()
{
	// プレイヤーの初期化
	x = 300;
	y = 300;
}

void Player::Update()
{
	// 移動
	if (CheckHitKey(KEY_INPUT_A))x -= 5;
	if (CheckHitKey(KEY_INPUT_D))x += 5;
	if (CheckHitKey(KEY_INPUT_W))y -= 5;
	if (CheckHitKey(KEY_INPUT_S))y += 5;

	// 画面外防止
	if (x < 0)x = 0;
	if (x > 630)x = 630;
	if (y < 0)y = 0;
	if (y > 470)y = 470;
}

void Player::Draw(int Image)
{
	DrawGraph(x, y, Image, TRUE);
}
