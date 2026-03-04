#pragma once
#include <fstream>
#include <assert.h>

#include "Surface.h"
#include "SpriteEffect.h"
#include "Graphics.h"
#include "Rect.h"
#include "Tile.h"
#include "GridUtils.h"
#include "DirectionUtils.h"
#include "Ghost.h"

class Maze
{
public:
	Maze();
	void Draw(Graphics& gfx) const;

public:
	bool CanEnter(GridUtils::GridPos gridPos) const;
	GridUtils::GridPos GetGridPos(int i) const;
	Vec2 GetPosOfTileAt(GridUtils::GridPos gridPos) const;
	RectF GetRectOfTileAt(GridUtils::GridPos gridPos) const;
	GridUtils::GridPos GetPacManSpawnPointGridPos() const;
	GridUtils::GridPos GetGhostSpawnPointGridPos(Ghost::Identity identity) const;
	int GetNumberOfTilesY() const;
	Tile::Type ConsumeDotAt(GridUtils::GridPos gridPos);

private:
	void SetupTiles();
	Tile GetTileAt(GridUtils::GridPos gridPos) const;
	Tile& GetTileAt(GridUtils::GridPos gridPos);
	void SetTileAt(GridUtils::GridPos gridPos, Tile tile);

private:
	static constexpr int tileSize = GridUtils::tileSize;
	static constexpr int nTilesX = 19;
	static constexpr int nTilesY = 22;
	static constexpr int nTiles = nTilesX * nTilesY;

	Tile tiles[nTilesX * nTilesY];
	Surface spriteTiles = Surface{ "Files/Images/Sprites/tiles.bmp" };
};