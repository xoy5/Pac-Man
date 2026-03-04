#pragma once
#include <string.h>

#include "Character.h"
#include "Animation.h"
#include "Vec2.h"

#include "GridUtils.h"
#include "Controller.h"
#include "DirectionUtils.h"
#include "GridUtils.h"

class MazeCharacter : public Character
{
public:
	MazeCharacter(const Maze& maze, Controller* pController,const std::string& spriteFilePath, const GridUtils::GridPos& gridPos, float speed, int width, int height, int nFrames, float frameHoldTime, bool animationPingPong = false);
	MazeCharacter(const Maze& maze, Controller* pController, const GridUtils::GridPos& gridPos, float speed, int width, int height);
	virtual void Update(float dt, Maze& maze);
	virtual void SetMoveDirection(const Maze& maze);
	virtual void ContinueMoveDirection(const Maze& maze) = 0;
	void SnapToGrid(const Maze& maze);
	virtual void OnGridPositionChanged(Maze& maze);

public:
	GridUtils::GridPos GetNextGridPos() const;
	bool IsMovedToNextGridPos(const Maze& maze) const;

protected:
	Controller* pController;
	GridUtils::GridPos gridPos;
	DirectionUtils::MoveDirection curMoveDirection = DirectionUtils::MoveDirection::None;
	DirectionUtils::MoveDirection nextMoveDirection = DirectionUtils::MoveDirection::None;
};