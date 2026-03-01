#pragma once
#include "DirectionUtils.h"

namespace GridUtils
{
	constexpr int tileSize = 16;
	struct GridPos
	{
		int x = 0;
		int y = 0;
	};
	GridPos GetGridPosBasedOnMoveDirection(const GridPos& gridPos, DirectionUtils::MoveDirection m);
}