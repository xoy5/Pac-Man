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
		Dots,
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
		//if (type == Type::Undefined || !sprite) return;

		const int srcX = (tileIndex % nRowSprite) * GridUtils::tileSize;
		const int srcY = (tileIndex / nRowSprite) * GridUtils::tileSize;

		const RectI srcRect = { srcX, srcX + GridUtils::tileSize, srcY, srcY + GridUtils::tileSize };

		gfx.DrawSprite(gridPos.x * size, gridPos.y * size, srcRect, *sprite, SpriteEffect::Copy{});
	}
	void SetTileIndex(const Tile& l, const Tile& r, const Tile& t, const Tile& b, const Tile& tL, const Tile& tR, const Tile& bL, const Tile& bR)
	{
		if (type != Type::Wall) {
			tileIndex = 0;
			return;
		}

		const bool L = (l.type == type);
		const bool R = (r.type == type);
		const bool T = (t.type == type);
		const bool B = (b.type == type);
		const bool TL = (tL.type == type);
		const bool TR = (tR.type == type);
		const bool BL = (bL.type == type);
		const bool BR = (bR.type == type);

		int mask = (L * lBit) | (R * rBit) | (T * tBit) | (B * bBit);

		if (T && L && R && TL && TR) tileIndex = bWBit;
		else if (B && L && R && BL && BR) tileIndex = tWBit;
		else if (L && T && B && TL && BL) tileIndex = rWBit;
		else if (R && T && B && TR && BR) tileIndex = lWBit;

		else if (T && L && !R && TL) tileIndex = tLCBit;
		else if (T && R && !L && TR) tileIndex = tRCBit;
		else if (B && L && !R && BL) tileIndex = bLCBit;
		else if (B && R && !L && BR) tileIndex = bRCBit;

		else tileIndex = mask;
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
	int tileIndex = 0;

	static constexpr int lBit = 0b0001;
	static constexpr int rBit = 0b0010;
	static constexpr int tBit = 0b0100;
	static constexpr int bBit = 0b1000;

	static constexpr int lWBit = 16;
	static constexpr int rWBit = 17;
	static constexpr int tWBit = 18;
	static constexpr int bWBit = 19;

	static constexpr int tLCBit = 20;
	static constexpr int tRCBit = 21;
	static constexpr int bLCBit = 22;
	static constexpr int bRCBit = 23;

	static constexpr RectI rectSpriteTileFloor = { GridUtils::tileSize * 0, GridUtils::tileSize * 1, GridUtils::tileSize * 0, GridUtils::tileSize * 1 };
};