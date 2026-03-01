#pragma once
#include "DirectionUtils.h"

namespace GridUtils
{
	constexpr int tileSize = 16;
	class GridPos
	{
	public:
		GridPos(int x, int y)
			:
			x(x),
			y(y)
		{
		}

		int x = 0;
		int y = 0;
	};
	GridPos GetGridPosBasedOnMoveDirection(const GridPos& gridPos, DirectionUtils::MoveDirection m)
	{
		switch (m)
		{
		case DirectionUtils::MoveDirection::Left:  return { gridPos.x - 1, gridPos.y };
		case DirectionUtils::MoveDirection::Right: return { gridPos.x + 1, gridPos.y };
		case DirectionUtils::MoveDirection::Up:    return { gridPos.x, gridPos.y - 1 };
		case DirectionUtils::MoveDirection::Down:  return { gridPos.x, gridPos.y + 1 };
		default:          return gridPos;
		}
	}
}