#pragma once
#include "Graphics.h"
#include "Surface.h"
#include "GridUtils.h"
#include "SpriteEffect.h"
#include "Rect.h"

class Tile
{
public:
	enum class Type
	{
		Undefined,
		Floor,
		Wall,
		Gate,
		ConnectorL,
		ConnectorR,
		PacManSpawn,
		BlinkySpawn,
		PinkySpawn,
		InkySpawn,
		ClydeSpawn
	};

public:
	Tile() = default;
	Tile(Type type, const Surface* sprite)
		:
		type(type),
		sprite(sprite),
		nRowSprite(sprite != nullptr ? (sprite->GetWidth() / GridUtils::tileSize) : 0)
	{
	}
	void Draw(Graphics& gfx, const GridUtils::GridPos& gridPos, int size) const
	{
		switch (type)
		{
		case Type::Floor:
			gfx.DrawSprite(gridPos.x * size, gridPos.y * size, rectSpriteTileFloor, *sprite, SpriteEffect::Copy{});
			break;
		case Type::Wall:
			gfx.DrawSprite(gridPos.x * size, gridPos.y * size,
				{
					(maskNeighbors % nRowSprite) * GridUtils::tileSize,
					((maskNeighbors % nRowSprite) + 1) * GridUtils::tileSize,
					(maskNeighbors / nRowSprite) * GridUtils::tileSize,
					((maskNeighbors / nRowSprite) + 1) * GridUtils::tileSize,
				}, *sprite, SpriteEffect::Copy{});
			break;
		}
	}
	void SetNeighbors(const Tile& l, const Tile& r, const Tile& t, const Tile& b, const Tile& tL, const Tile& tR, const Tile& bL, const Tile& bR)
	{
		if (l.GetType() == type) maskNeighbors += lBit;
		if (r.GetType() == type) maskNeighbors += rBit;
		if (t.GetType() == type) maskNeighbors += tBit;
		if (b.GetType() == type) maskNeighbors += bBit;

		if (((maskNeighbors & tBit) && (maskNeighbors & lBit) && (maskNeighbors & rBit)) && tL.GetType() == type && tR.GetType() == type) maskNeighbors -= tBit;
		if (((maskNeighbors & bBit) && (maskNeighbors & lBit) && (maskNeighbors & rBit)) && bL.GetType() == type && bR.GetType() == type) maskNeighbors -= bBit;
		if (((maskNeighbors & lBit) && (maskNeighbors & tBit) && (maskNeighbors & bBit)) && tL.GetType() == type && bL.GetType() == type) maskNeighbors -= lBit;
		if (((maskNeighbors & rBit) && (maskNeighbors & tBit) && (maskNeighbors & bBit)) && tR.GetType() == type && bR.GetType() == type) maskNeighbors -= rBit;
	}
public:
	void SetType(Type type_in)
	{
		type = type_in;
	}
	Type GetType() const
	{
		return type;
	}

private:
	Type type;
	const Surface* sprite;
	int nRowSprite;
	int maskNeighbors = 0;
	static constexpr int lBit = 1;
	static constexpr int rBit = 2;
	static constexpr int tBit = 4;
	static constexpr int bBit = 8;

	static constexpr RectI rectSpriteTileFloor = { GridUtils::tileSize * 0, GridUtils::tileSize * 1, GridUtils::tileSize * 0, GridUtils::tileSize * 1 };
};