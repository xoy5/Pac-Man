#pragma once
#include <string>
#include <utility>
#include <map>

#include "Graphics.h"
#include "Vec2.h"
#include "Rect.h"

#include "MazeCharacter.h"
#include "GridUtils.h"

class Maze;

class Ghost : public MazeCharacter
{
public: 
    enum class Identity { Blinky, Pinky, Inky, Clyde };

public:
    Ghost(Identity identity, const Maze& maze, Controller* pController, const MazeCharacter* pTarget);
	void ContinueMoveDirection(const Maze& maze) override;

public:
	void SetTarget(const MazeCharacter* pTarget_in);

private:
	const MazeCharacter* pTarget = nullptr;
    Identity identity;
};