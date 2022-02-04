#include "pch.h"
#include "Player.h"

void Player::LineDeleteSuccess(int count)
{
	_score += (10 * count);
}

int Player::GetScore()
{
	return _score;
}
