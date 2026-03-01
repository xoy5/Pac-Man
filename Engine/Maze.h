#pragma once
#include <fstream>
#include <assert.h>

#include "Surface.h"
#include "SpriteEffect.h"
#include "Graphics.h"
#include "Rect.h"
#include "Tile.h"
#include "GridUtils.h"

class Maze
{
public:
	Maze()
	{
		SetupTiles();
	}
	void ResetToDefault()
	{
		SetupTiles();
	}
	void Draw(Graphics& gfx) const
	{
		for (int i = 0; i < nTiles; i++)
		{
			tiles[i].Draw(gfx, GetGridPos(i), tileSize);
		}
	}

public:
	bool CanEnter(GridUtils::GridPos gridPos) const
	{
		return GetTileAt(gridPos).GetType() != Tile::Type::Wall;
	}
	GridUtils::GridPos GetGridPos(int i) const
	{
		return GridUtils::GridPos{ i % nTilesX, i / nTilesX };
	}
	Vec2 GetPosOfTileAt(GridUtils::GridPos gridPos) const
	{
		return Vec2{ float(gridPos.x * tileSize), float(gridPos.y * tileSize) };
	}
	RectF GetRectOfTileAt(GridUtils::GridPos gridPos) const
	{
		return RectF(Vec2{ float(gridPos.x * tileSize), float(gridPos.y * tileSize) }, float(tileSize), float(tileSize));
	}
	GridUtils::GridPos GetPacManSpawnPointGridPos() const
	{
		for (int i = 0; i < nTiles; i++)
		{
			if (tiles[i].GetType() == Tile::Type::PacManSpawn)
			{
				return GetGridPos(i);
			}
		}
		assert(false && "No PacMan spawn point.");
		return GridUtils::GridPos{ -1,-1 };
	}

	int GetNumberOfTilesX() const
	{
		return nTilesX;
	}
	int GetNumberOfTilesY() const
	{
		return nTilesY;
	}
	int GetTileSize() const
	{
		return tileSize;
	}

private:
	void SetupTiles()
	{
		std::ifstream file("Files/Data/maze.txt");
		assert(file && "File Error");

		char c;
		int i = 0;
		while (file.get(c))
		{
			switch (c)
			{
			case '\n':
				i--;
				break;
			case 'W':
				tiles[i] = Tile{ Tile::Type::Wall, &spriteTiles };
				break;
			case 'F':
				tiles[i] = Tile{ Tile::Type::Floor, &spriteTiles };
				break;
			case 'S':
				tiles[i] = Tile{ Tile::Type::PacManSpawn, &spriteTiles };
				break;
			default:
				tiles[i] = Tile{ Tile::Type::Floor, &spriteTiles };
			}
			i++;
		}
	}
	Tile GetTileAt(GridUtils::GridPos gridPos) const
	{
		assert(gridPos.x >= 0 && gridPos.x < nTilesX &&
			gridPos.y >= 0 && gridPos.y < nTilesY);

		return tiles[gridPos.y * nTilesX + gridPos.x];
	}
	void SetTileAt(GridUtils::GridPos gridPos, Tile tile)
	{
		tiles[gridPos.y * nTilesX + gridPos.x] = tile;
	}

private:
	static constexpr int tileSize = GridUtils::tileSize;
	static constexpr int nTilesX = 19;
	static constexpr int nTilesY = 25;
	static constexpr int nTiles = nTilesX * nTilesY;

	Tile tiles[nTilesX * nTilesY];
	Surface spriteTiles = Surface{ "Files/Images/Sprites/tiles.bmp" };
};