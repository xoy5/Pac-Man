#include "Controller.h"
#include "MazeCharacter.h"

PlayerController::PlayerController(const Keyboard* pKbd)
	:
	pKbd(pKbd)
{
}

DirectionUtils::MoveDirection PlayerController::GetMoveDirection() const
{
	Vec2 dir(0.0f, 0.0f);

	if (pKbd->KeyIsPressed('A')) dir.x += -1.0f;
	if (pKbd->KeyIsPressed('D')) dir.x += 1.0f;
	if (pKbd->KeyIsPressed('W')) dir.y += -1.0f;
	if (pKbd->KeyIsPressed('S')) dir.y += 1.0f;

	return DirectionUtils::Vec2ToMoveDirection(dir);
}

BotController::BotController(Behavior behavior, const Maze* pMaze, const MazeCharacter* pTarget)
	:
	behavior(behavior),
	pMaze(pMaze),
	pTarget(pTarget)
{
}

DirectionUtils::MoveDirection BotController::GetMoveDirection() const
{
	switch (behavior)
	{
	case Behavior::Wander:
		return GetRandomDirection();
	case Behavior::Pursuit:
		return GetDirectionToTarget();
	default:
		return DirectionUtils::MoveDirection::None;
	}
}
DirectionUtils::MoveDirection BotController::GetRandomDirection() const
{
	return DirectionUtils::MoveDirection::Right;
}

DirectionUtils::MoveDirection BotController::GetDirectionToTarget() const
{
	return DirectionUtils::MoveDirection::Right;
}
