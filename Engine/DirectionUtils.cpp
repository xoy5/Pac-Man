#include "DirectionUtils.h"

namespace DirectionUtils
{
	MoveDirection Vec2ToMoveDirection(const Vec2& dir)
	{
		if (dir.x > 0.0f) return MoveDirection::Right;
		if (dir.x < 0.0f) return MoveDirection::Left;
		if (dir.y > 0.0f) return MoveDirection::Down;
		if (dir.y < 0.0f) return MoveDirection::Up;
		return MoveDirection::None;
	}

	Vec2 MoveDirectionToVec2(MoveDirection dir)
	{
		switch (dir)
		{
		case MoveDirection::Left:  return { -1.0f,  0.0f };
		case MoveDirection::Right: return { 1.0f,  0.0f };
		case MoveDirection::Up:    return { 0.0f, -1.0f };
		case MoveDirection::Down:  return { 0.0f,  1.0f };
		default:                   return { 0.0f,  0.0f };
		}
	}

	bool IsOpposite(MoveDirection first, MoveDirection second)
	{
		if (first == MoveDirection::Left && second == MoveDirection::Right) return true;
		if (first == MoveDirection::Right && second == MoveDirection::Left) return true;
		if (first == MoveDirection::Up && second == MoveDirection::Down)    return true;
		if (first == MoveDirection::Down && second == MoveDirection::Up)    return true;

		return false;
	}

}
