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
	if (CheckHitKey(KEY_INPUT_LEFT))x -= 5;
	if (CheckHitKey(KEY_INPUT_RIGHT))x += 5;
	if (CheckHitKey(KEY_INPUT_UP))y -= 5;
	if (CheckHitKey(KEY_INPUT_DOWN))y += 5;

	// 画面外防止
	if (x < 0)x = 0;
	if (x > 630)x = 630;
	if (y < 0)y = 0;
	if (y > 470)y = 470;
}

void Player::Draw()
{
	// プレイヤー描画
	DrawBox(x - 10, y - 10, x + 10, y + 10, GetColor(0, 0, 0), TRUE);
}
