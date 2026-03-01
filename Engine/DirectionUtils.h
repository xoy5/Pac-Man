#pragma once
#include "Vec2.h"    

namespace DirectionUtils
{
	enum class MoveDirection
	{
		None = 0,
		Left,
		Right,
		Up,
		Down
	};
	MoveDirection Vec2ToMoveDirection(const Vec2& dir);
	Vec2 MoveDirectionToVec2(MoveDirection dir);
	bool IsOpposite(MoveDirection first, MoveDirection second);
}