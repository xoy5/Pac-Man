#include "MazeCharacter.h"

MazeCharacter::MazeCharacter(const Maze& maze, Controller* pController, const std::string& spriteFilePath, const GridUtils::GridPos& gridPos, float speed, int width, int height, int nFrames, float frameHoldTime, bool animationPingPong)
	:
	Character(spriteFilePath, maze.GetPosOfTileAt(gridPos), speed, width, height, nFrames, frameHoldTime, animationPingPong),
	pController(pController),
	gridPos(gridPos)
{
	Character::SetStandingDirection(DirectionUtils::MoveDirectionToVec2(DirectionUtils::MoveDirection::Up));
}

MazeCharacter::MazeCharacter(const Maze& maze, Controller* pController, const GridUtils::GridPos& gridPos, float speed, int width, int height)
	:
	Character(maze.GetPosOfTileAt(gridPos), speed, width, height),
	pController(pController),
	gridPos(gridPos)
{
	Character::SetStandingDirection(DirectionUtils::MoveDirectionToVec2(DirectionUtils::MoveDirection::Up));
}

void MazeCharacter::Update(float dt, const Maze& maze)
{
	Character::SetDirection(DirectionUtils::MoveDirectionToVec2(curMoveDirection));
	if (curMoveDirection == DirectionUtils::MoveDirection::None) return;

	Character::Update(dt);

	if (IsMovedToNextGridPos(maze))
	{
		gridPos = GetNextGridPos();
		SnapToGrid(maze);
		ContinueMoveDirection(maze);
	}
}

void MazeCharacter::SetMoveDirection(const Maze& maze)
{
	DirectionUtils::MoveDirection inputMoveDirection = pController->GetMoveDirection();
	if (inputMoveDirection == DirectionUtils::MoveDirection::None) return;

	// Immediate move if standing still
	if (curMoveDirection == DirectionUtils::MoveDirection::None)
	{
		if (maze.CanEnter(GridUtils::GetGridPosBasedOnMoveDirection(gridPos, inputMoveDirection)))
		{
			curMoveDirection = inputMoveDirection;
		}
		else
		{
			Character::SetStandingDirection(DirectionUtils::MoveDirectionToVec2(inputMoveDirection));
		}
	}
	// Queue the move to be processed at the next tile junction
	else
	{
		nextMoveDirection = inputMoveDirection;
	}
}

GridUtils::GridPos MazeCharacter::GetNextGridPos() const
{
	return GridUtils::GetGridPosBasedOnMoveDirection(gridPos, curMoveDirection);
}

void MazeCharacter::SnapToGrid(const Maze& maze)
{
	SetPos(maze.GetPosOfTileAt(gridPos));
}

bool MazeCharacter::IsMovedToNextGridPos(const Maze& maze) const
{
	const RectF ownerRect = Character::GetRect();
	const RectF nextTileRect = maze.GetRectOfTileAt(GetNextGridPos());

	switch (curMoveDirection)
	{
	case DirectionUtils::MoveDirection::Left:
		return ownerRect.right <= nextTileRect.right;
	case DirectionUtils::MoveDirection::Right:
		return ownerRect.left >= nextTileRect.left;
	case DirectionUtils::MoveDirection::Up:
		return ownerRect.bottom <= nextTileRect.bottom;
	case DirectionUtils::MoveDirection::Down:
		return ownerRect.top >= nextTileRect.top;

	default:
		return true;
	}
}