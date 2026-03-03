#pragma once
#include "Keyboard.h"
#include "Vec2.h"

#include "DirectionUtils.h"
#include "GridUtils.h"

class Maze;
class MazeCharacter;

class Controller
{
public:
	Controller() = default;
	virtual	DirectionUtils::MoveDirection GetMoveDirection() const = 0;
};

class PlayerController : public Controller
{
public:
	enum class KeyboardControll
	{
		WSAD,
		ARROWS
	};
public:
	PlayerController(const Keyboard* pKbd, KeyboardControll kC);
	DirectionUtils::MoveDirection GetMoveDirection() const override;

private:
	const Keyboard* pKbd;
	KeyboardControll kC;
};

class BotController : public Controller
{
public:
	enum class Behavior {
		Wander,
		Pursuit
	};
public:
	BotController(Behavior behavior, const Maze* pMaze, const MazeCharacter* pTarget);
	DirectionUtils::MoveDirection GetMoveDirection() const override;

private:
	DirectionUtils::MoveDirection GetRandomDirection() const;
	DirectionUtils::MoveDirection GetDirectionToTarget() const;


private:
	Behavior behavior;
	const Maze* pMaze;
	const MazeCharacter* pTarget;
};

//void CalculateAndSetDirection(const Maze& maze)
//{
//	if (movement.IsMovedToNextTile(maze, *this) || movement.IsMoving() == false || movement.IsNextMoveReserved() == false)
//	{
//		if (movement.IsMoving() == false)
//		{
//			algorithmRunCount++;
//			const auto currentPosTile = GetTilePos();
//			const auto targetPosTile = pTarget->GetTilePos();
//
//			const auto nextPosTile = CalculateBFS(maze, currentPosTile, targetPosTile);
//
//			const Vec2 dir = Movement::GetDirectionFromTiles(currentPosTile, nextPosTile);
//			MazeCharacter::SetMovementDirection(dir, maze);
//		}
//		if (movement.IsNextMoveReserved() == false)
//		{
//			algorithmRunCount++;
//			const auto nextPosTile = GetNextTilePos();
//			const auto targetPosTile = pTarget->GetTilePos();
//
//			const auto nextnextPosTile = CalculateBFS(maze, nextPosTile, targetPosTile);
//
//			const Vec2 dir = Movement::GetDirectionFromTiles(nextPosTile, nextnextPosTile);
//			MazeCharacter::SetMovementDirection(dir, maze);
//		}
//	}
//}
//std::pair<int, int> CalculateBFS(const Maze& maze, std::pair<int, int> startPosTile, std::pair<int, int> targetPosTile)
//{
//	if (startPosTile == targetPosTile) return startPosTile;
//
//	std::queue<std::pair<int, int>> q;
//	q.push(startPosTile);
//
//	std::map<std::pair<int, int>, std::pair<int, int>> parent;
//	parent[startPosTile] = startPosTile;
//
//	const std::vector<std::pair<int, int>> directions = { {1,0}, {-1,0}, {0,1}, {0,-1} };
//
//	bool found = false;
//	while (!q.empty())
//	{
//		std::pair<int, int> current = q.front();
//		q.pop();
//
//		if (current == targetPosTile)
//		{
//			found = true;
//			break;
//		}
//
//		for (const auto& d : directions)
//		{
//			std::pair<int, int> next = { current.first + d.first, current.second + d.second };
//
//			if (maze.CanEnter(next) && parent.find(next) == parent.end())
//			{
//				parent[next] = current;
//				q.push(next);
//			}
//		}
//	}
//
//	if (found)
//	{
//		std::pair<int, int> step = targetPosTile;
//
//		while (parent[step] != startPosTile)
//		{
//			step = parent[step];
//		}
//		return step;
//	}
//
//	return startPosTile;
//}