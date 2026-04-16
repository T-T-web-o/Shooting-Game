#include "Player.h"
#include "DxLib.h"

Player::Player()
{
	x = 300;
	y = 300;
}

void Player::Update()
{
	if (CheckHitKey(KEY_INPUT_LEFT))x -= 5;
	if (CheckHitKey(KEY_INPUT_RIGHT))x += 5;
	if (CheckHitKey(KEY_INPUT_UP))y -= 5;
	if (CheckHitKey(KEY_INPUT_DOWN))y += 5;
}

void Player::Draw()
{
	DrawBox(x - 10, y - 10, x + 10, y + 10, GetColor(255, 255, 255), TRUE);
}
