#include "Controller.h"

#include "Maze.h"
#include "MazeCharacter.h"

PlayerController::PlayerController(const Keyboard* pKbd, KeyboardControll kC)
	:
	pKbd(pKbd),
	kC(kC)
{
}

DirectionUtils::MoveDirection PlayerController::GetMoveDirection() const
{
	Vec2 dir(0.0f, 0.0f);

	switch (kC)
	{
	case PlayerController::KeyboardControll::WSAD:
		if (pKbd->KeyIsPressed('A')) dir.x += -1.0f;
		if (pKbd->KeyIsPressed('D')) dir.x += 1.0f;
		if (pKbd->KeyIsPressed('W')) dir.y += -1.0f;
		if (pKbd->KeyIsPressed('S')) dir.y += 1.0f;
		break;
	case PlayerController::KeyboardControll::ARROWS:
		if (pKbd->KeyIsPressed(VK_LEFT)) dir.x += -1.0f;
		if (pKbd->KeyIsPressed(VK_RIGHT)) dir.x += 1.0f;
		if (pKbd->KeyIsPressed(VK_UP)) dir.y += -1.0f;
		if (pKbd->KeyIsPressed(VK_DOWN)) dir.y += 1.0f;
		break;
	default:
		break;
	}

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
	return DirectionUtils::MoveDirection::None;
}

DirectionUtils::MoveDirection BotController::GetDirectionToTarget() const
{
	return DirectionUtils::MoveDirection::None;
}
