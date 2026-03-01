#include "GridUtils.h"

namespace GridUtils
{
    GridPos GridUtils::GetGridPosBasedOnMoveDirection(const GridPos& gridPos, DirectionUtils::MoveDirection m)
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
