#include "Item.h"
#include "DxLib.h"

//============================================================
// アイテム関連の定数
//============================================================

const int ITEM_MOVE_SPEED = 2;       // アイテムの移動速度
const int ITEM_HIT_RANGE = 35;       // プレイヤーとの当たり判定範囲
const int ITEM_POWER_UP = 50;        // POWERアイテムの攻撃力上昇値
const int ITEM_HP_UP = 1;            // HPアイテムの体力上昇値
const int ITEM_SCREEN_BOTTOM = 500;  // アイテムを削除する画面下端
const int ITEM_DRAW_SIZE = 10;       // アイテムの描画サイズ

// アイテムの色
const int POWER_COLOR = GetColor(255, 0, 0);
const int HP_COLOR = GetColor(0, 255, 0);


Item::Item(int x, int y, ItemType type)
{
	this->x = x;
	this->y = y;
	this->type = type;
	isDead = false;
}

void Item::Update(Player&player)
{
	// 下方向に移動
	y += ITEM_MOVE_SPEED;

	// プレイヤーとの当たり判定
	if (abs(x - player.x) < ITEM_HIT_RANGE &&
		abs(y - player.y) < ITEM_HIT_RANGE)
	{
		switch (type)
		{
		case POWER:
			player.bulletDamage += ITEM_POWER_UP;
			break;

		case HP:
			player.hp += ITEM_HP_UP;
			break;
		}
		// アイテム取得したので削除
		isDead = true;
	}

	// 画面外に出たら削除
	if (y > ITEM_SCREEN_BOTTOM)
	{
		isDead = true;
	}
}

void Item::Draw()
{
	int color;

	switch (type)
	{
	case POWER:
		color = POWER_COLOR;
		break;
	case HP:
		color = HP_COLOR;
		break;
	}

	DrawBox(x - ITEM_DRAW_SIZE, y - ITEM_DRAW_SIZE, x + ITEM_DRAW_SIZE, y + ITEM_DRAW_SIZE, color, TRUE);
}
