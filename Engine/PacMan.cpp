#include "PacMan.h"

PacMan::PacMan(const Maze& maze, Controller* pController)
	:
	MazeCharacter(maze, pController, "Files/Images/Sprites/pacMan.bmp", maze.GetPacManSpawnPointGridPos(), 100.0f, GridUtils::tileSize, GridUtils::tileSize, 3, 0.08f, true)
{
}

void PacMan::Update(float dt, Maze& maze)
{
	powerMode.Update(dt);
	MazeCharacter::Update(dt, maze);
}

void PacMan::SetMoveDirection(const Maze& maze)
{
	{
		DirectionUtils::MoveDirection inputMoveDirection = pController->GetMoveDirection();
		if (inputMoveDirection == DirectionUtils::MoveDirection::None) return;

		// Handle instantaneous 180-degree turns
		if (DirectionUtils::IsOpposite(inputMoveDirection, curMoveDirection))
		{
			gridPos = MazeCharacter::GetNextGridPos();
			curMoveDirection = inputMoveDirection;
			nextMoveDirection = DirectionUtils::MoveDirection::None;
			return;
		}

		MazeCharacter::SetMoveDirection(maze);
	}
}

void PacMan::ContinueMoveDirection(const Maze& maze)
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

void PacMan::OnGridPositionChanged(Maze& maze)
{
	switch (maze.ConsumeDotAt(gridPos))
	{
		case Tile::Type::PowerDot:
			powerMode.Activate();
			break;
		case Tile::Type::Dot:
			break;
	}
}

bool PacMan::IsPowerModeActive() const
{
	return powerMode.isActive;
}
