#pragma once
#include <string>
#include <utility>
#include <map>

#include "Graphics.h"
#include "Vec2.h"
#include "Rect.h"

#include "MazeCharacter.h"
#include "Maze.h"
#include "GridUtils.h"

class Ghost : public MazeCharacter
{
public: 
    enum class Identity { Blinky, Pinky, Inky, Clyde };
public:
    Ghost(Identity color, const Maze& maze, Controller* pController, const MazeCharacter* pTarget)
        :
        MazeCharacter(maze, pController, maze.GetPacManSpawnPointGridPos()/*spawn*/, 105.0f, GridUtils::tileSize, GridUtils::tileSize),
		pTarget(pTarget),
        identity(identity)
	{
        switch (color)
        {
        case Identity::Blinky:
            Character::SetSprite("Files/Images/Sprites/Ghosts/blinky.bmp", 2, 0.05f);
            break;
        case Identity::Pinky:
            Character::SetSprite("Files/Images/Sprites/Ghosts/pinky.bmp", 2, 0.05f);
            break;
        case Identity::Inky:
            Character::SetSprite("Files/Images/Sprites/Ghosts/inky.bmp", 2, 0.05f);
            break;
        case Identity::Clyde:
            Character::SetSprite("Files/Images/Sprites/Ghosts/clyde.bmp", 2, 0.05f);
            break;
        }
    }
    void ContinueMoveDirection(const Maze& maze) override
    {
        // Check if the queued next move is valid to perform a turn
        if (nextMoveDirection != DirectionUtils::MoveDirection::None
            && DirectionUtils::IsOpposite(curMoveDirection, nextMoveDirection) == false
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

public:
	void SetTarget(const MazeCharacter* pTarget_in)
	{
		pTarget = pTarget_in;
	}

private:
	const MazeCharacter* pTarget = nullptr;
    Identity identity;
};