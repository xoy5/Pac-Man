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
    struct PowerMode 
    {
        bool isActive = false;
        float timer = 0.0f;
        const float duration = 8.0f;

        void Update(float dt) {
            if (isActive) {
                timer -= dt;
                if (timer <= 0) isActive = false;
            }
        }
        void Activate() {
            isActive = true;
            timer = duration;
        }
    } powerMode;

public:
	PacMan(const Maze& maze, Controller* pController);
    void Update(float dt, Maze& maze) override;
	void SetMoveDirection(const Maze& maze) override;
	void ContinueMoveDirection(const Maze& maze) override;
	void OnGridPositionChanged(Maze& maze) override;

public:
    bool IsPowerModeActive() const;
};