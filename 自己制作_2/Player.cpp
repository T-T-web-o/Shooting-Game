#include "Player.h"
#include "DxLib.h"

Player::Player()
{
	// ˆÊ’u‰Šú‰»
	x = 300;
	y = 300;
}

void Player::Update()
{
	// ˆÚ“®
	if (CheckHitKey(KEY_INPUT_A))x -= 5;
	if (CheckHitKey(KEY_INPUT_D))x += 5;
	if (CheckHitKey(KEY_INPUT_W))y -= 5;
	if (CheckHitKey(KEY_INPUT_S))y += 5;

	// ‰æ–ÊŠO–h~
	if (x < 0)x = 0;
	if (x > 630)x = 630;
	if (y < 0)y = 0;
	if (y > 470)y = 470;
}

void Player::Draw(int Image)
{
	// w’è‚³‚ê‚½‰æ‘œ‚ğ•`‰æ
	DrawGraph(x, y, Image, TRUE);
}
