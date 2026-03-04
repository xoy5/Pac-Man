#include "Maze.h"

Maze::Maze()
{
	SetupTiles();
}

void Maze::Draw(Graphics& gfx) const
{
	for (int i = 0; i < nTiles; i++)
	{
		tiles[i].Draw(gfx, GetGridPos(i), tileSize);
	}
}

bool Maze::CanEnter(GridUtils::GridPos gridPos) const
{
	return GetTileAt(gridPos).GetType() != Tile::Type::Wall;
}

GridUtils::GridPos Maze::GetGridPos(int i) const
{
	return GridUtils::GridPos{ i % nTilesX, i / nTilesX };
}

Vec2 Maze::GetPosOfTileAt(GridUtils::GridPos gridPos) const
{
	return Vec2{ float(gridPos.x * tileSize), float(gridPos.y * tileSize) };
}

RectF Maze::GetRectOfTileAt(GridUtils::GridPos gridPos) const
{
	return RectF(Vec2{ float(gridPos.x * tileSize), float(gridPos.y * tileSize) }, float(tileSize), float(tileSize));
}

GridUtils::GridPos Maze::GetPacManSpawnPointGridPos() const
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

GridUtils::GridPos Maze::GetGhostSpawnPointGridPos(Ghost::Identity identity) const
{
	Tile::Type type = Tile::Type::Undefined;
	switch (identity)
	{
	case Ghost::Identity::Blinky:
		type = Tile::Type::BlinkySpawn;
		break;
	case Ghost::Identity::Pinky:
		type = Tile::Type::PinkySpawn;
		break;
	case Ghost::Identity::Inky:
		type = Tile::Type::InkySpawn;
		break;
	case Ghost::Identity::Clyde:
		type = Tile::Type::ClydeSpawn;
		break;
	default:
		type = Tile::Type::Undefined;
	}
	for (int i = 0; i < nTiles; i++)
	{
		if (tiles[i].GetType() == type)
		{
			return GetGridPos(i);
		}
	}
	assert(false && "No Ghost spawn point.");
	return GridUtils::GridPos{ -1,-1 };
}

int Maze::GetNumberOfTilesY() const
{
	return nTilesY;
}

void Maze::SetupTiles()
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
		case 'F':
			tiles[i] = Tile{ Tile::Type::Floor, &spriteTiles };
			break;
		case 'D':
			tiles[i] = Tile{ Tile::Type::Dot, &spriteTiles };
			break;
		case 'X':
			tiles[i] = Tile{ Tile::Type::PowerDot, &spriteTiles };
			break;
		case 'G':
			tiles[i] = Tile{ Tile::Type::Gate, &spriteTiles };
			break;
		case 'W':
			tiles[i] = Tile{ Tile::Type::Wall, &spriteTiles };
			break;
		case 'L':
			tiles[i] = Tile{ Tile::Type::ConnectorL, &spriteTiles };
			break;
		case 'R':
			tiles[i] = Tile{ Tile::Type::ConnectorR, &spriteTiles };
			break;
		case 'S':
			tiles[i] = Tile{ Tile::Type::PacManSpawn, &spriteTiles };
			break;
		case 'B':
			tiles[i] = Tile{ Tile::Type::BlinkySpawn, &spriteTiles };
			break;
		case 'P':
			tiles[i] = Tile{ Tile::Type::PinkySpawn, &spriteTiles };
			break;
		case 'I':
			tiles[i] = Tile{ Tile::Type::InkySpawn, &spriteTiles };
			break;
		case 'C':
			tiles[i] = Tile{ Tile::Type::ClydeSpawn, &spriteTiles };
			break;
		default:
			tiles[i] = Tile{ Tile::Type::Floor, &spriteTiles };
		}
		i++;
	}

	for (int i = 0; i < nTiles; i++)
	{
		GridUtils::GridPos gridPos = GetGridPos(i);
		GridUtils::GridPos gridPosUp = GridUtils::GetGridPosBasedOnMoveDirection(gridPos, DirectionUtils::MoveDirection::Up);
		GridUtils::GridPos gridPosDown = GridUtils::GetGridPosBasedOnMoveDirection(gridPos, DirectionUtils::MoveDirection::Down);
		tiles[i].SetTileWallIndex(
			GetTileAt(GridUtils::GetGridPosBasedOnMoveDirection(gridPos, DirectionUtils::MoveDirection::Left)),
			GetTileAt(GridUtils::GetGridPosBasedOnMoveDirection(gridPos, DirectionUtils::MoveDirection::Right)),
			GetTileAt(gridPosUp),
			GetTileAt(gridPosDown),
			GetTileAt(GridUtils::GetGridPosBasedOnMoveDirection(gridPosUp, DirectionUtils::MoveDirection::Left)),
			GetTileAt(GridUtils::GetGridPosBasedOnMoveDirection(gridPosUp, DirectionUtils::MoveDirection::Right)),
			GetTileAt(GridUtils::GetGridPosBasedOnMoveDirection(gridPosDown, DirectionUtils::MoveDirection::Left)),
			GetTileAt(GridUtils::GetGridPosBasedOnMoveDirection(gridPosDown, DirectionUtils::MoveDirection::Right))
		);
	}
}

Tile Maze::GetTileAt(GridUtils::GridPos gridPos) const
{
	if (!(gridPos.x >= 0 && gridPos.x < nTilesX && gridPos.y >= 0 && gridPos.y < nTilesY))
		return Tile(Tile::Type::Undefined, nullptr);

	return tiles[gridPos.y * nTilesX + gridPos.x];
}

Tile& Maze::GetTileAt(GridUtils::GridPos gridPos)
{
	if (!(gridPos.x >= 0 && gridPos.x < nTilesX && gridPos.y >= 0 && gridPos.y < nTilesY))
		return Tile(Tile::Type::Undefined, nullptr);

	return tiles[gridPos.y * nTilesX + gridPos.x];
}

void Maze::SetTileAt(GridUtils::GridPos gridPos, Tile tile)
{
	tiles[gridPos.y * nTilesX + gridPos.x] = tile;
}

Tile::Type Maze::ConsumeDotAt(GridUtils::GridPos gridPos)
{
	Tile& t = GetTileAt(gridPos);
	const Tile::Type tType = t.GetType();
	switch (tType)
	{
	case Tile::Type::PowerDot:
	case Tile::Type::Dot:
		t.SetTypeAndBasicIdx(Tile::Type::Floor);
	}

	return tType;
}
