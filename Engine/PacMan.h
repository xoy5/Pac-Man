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
	PacMan(const Maze& maze, Controller* pController);
	void SetMoveDirection(const Maze& maze) override;
	void ContinueMoveDirection(const Maze& maze) override;
};