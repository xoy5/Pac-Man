#pragma once
#include <string>
#include <utility>

#include "Graphics.h"
#include "Vec2.h"
#include "Rect.h"

#include "MazeCharacter.h"
#include "Maze.h"
#include "Controller.h"
#include "DirectionUtils.h"
#include "GridUtils.h"
#include "DirectionUtils.h"

class PacMan : public MazeCharacter
{
public:
	PacMan(const Maze& maze, Controller* pController)
		:
		MazeCharacter(maze, pController, "Files/Images/Sprites/ghostRed.bmp", maze.GetPacManSpawnPointGridPos(), 100.0f, GridUtils::tileSize, GridUtils::tileSize, 2, 0.05f)
	{
	}
	void SetMoveDirection(const Maze& maze) override
	{
		DirectionUtils::MoveDirection inputMoveDirection = pController->GetMoveDirection();
		if (inputMoveDirection == DirectionUtils::MoveDirection::None) return;

		// Handle instantaneous 180-degree turns
		if (DirectionUtils::IsOpposite(curMoveDirection, nextMoveDirection))
		{
			gridPos = MazeCharacter::GetNextGridPos();
			curMoveDirection = inputMoveDirection;
			//nextMoveDirection = DirectionUtils::MoveDirection::None;
			return;
		}

		MazeCharacter::SetMoveDirection(maze);
	}
	void ContinueMoveDirection(const Maze& maze) override
	{
		// Check if the queued next move is valid to perform a turn
		if (nextMoveDirection != DirectionUtils::MoveDirection::None
			&& maze.CanEnter(GridUtils::GetGridPosBasedOnMoveDirection(gridPos, nextMoveDirection)))
		{
			curMoveDirection = nextMoveDirection;
			nextMoveDirection = DirectionUtils::MoveDirection::None;
		}
		// If the current path is blocked, stop the movement
		else if (!maze.CanEnter(GridUtils::GetGridPosBasedOnMoveDirection(gridPos, curMoveDirection)))
		{
			curMoveDirection = DirectionUtils::MoveDirection::None;
			nextMoveDirection = DirectionUtils::MoveDirection::None;
		}
	}
};