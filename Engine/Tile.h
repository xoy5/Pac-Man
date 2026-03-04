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
		Dot,
		PowerDot,
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
		sprite(sprite),
		nColSprite(sprite != nullptr ? (sprite->GetWidth() / GridUtils::tileSize) : 0)
	{
		SetTypeAndBasicIdx(type);
	}
	void Draw(Graphics& gfx, const GridUtils::GridPos& gridPos, int size) const
	{
		assert(sprite && "Tile has not got pointer to sprite.");

		const int srcX = (tileIndex % nColSprite) * GridUtils::tileSize;
		const int srcY = (tileIndex / nColSprite) * GridUtils::tileSize;

		const RectI srcRect = { srcX, srcX + GridUtils::tileSize, srcY, srcY + GridUtils::tileSize };

		gfx.DrawSprite(gridPos.x * size, gridPos.y * size, srcRect, *sprite, SpriteEffect::Copy{});
	}
	void SetTileWallIndex(const Tile& l, const Tile& r, const Tile& t, const Tile& b,
		const Tile& tL, const Tile& tR, const Tile& bL, const Tile& bR)
	{
		if (type != Type::Wall) return;

		const bool L = (l.type == type);
		const bool R = (r.type == type);
		const bool T = (t.type == type);
		const bool B = (b.type == type);
		const bool TL = (tL.type == type);
		const bool TR = (tR.type == type);
		const bool BL = (bL.type == type);
		const bool BR = (bR.type == type);

		int neighborMask = (L ? maskL : 0) | (R ? maskR : 0) | (T ? maskT : 0) | (B ? maskB : 0);

		if (T && L && R && TL && TR)      tileIndex = idxWallB;
		else if (B && L && R && BL && BR) tileIndex = idxWallT;
		else if (L && T && B && TL && BL) tileIndex = idxWallR;
		else if (R && T && B && TR && BR) tileIndex = idxWallL;

		else if (T && L && !R && TL)      tileIndex = idxCornerTL;
		else if (T && R && !L && TR)      tileIndex = idxCornerTR;
		else if (B && L && !R && BL)      tileIndex = idxCornerBL;
		else if (B && R && !L && BR)      tileIndex = idxCornerBR;
		else if (L && R && T && B && TL && TR && BL && BR) tileIndex = idxFloor;
		else
		{
			tileIndex = neighborMask;
		}
	}

public:
	void SetTypeAndBasicIdx(Type type_in) 
	{ 
		type = type_in;
		switch (type)
		{
		case Type::Floor:
		case Type::Undefined:
		case Type::PacManSpawn:
		case Type::BlinkySpawn:
		case Type::PinkySpawn:
		case Type::InkySpawn:
		case Type::ClydeSpawn:
		case Type::ConnectorL:
		case Type::ConnectorR:
			tileIndex = idxFloor;
			break;
		case Type::Dot:
			tileIndex = idxDot;
			break;
		case Type::PowerDot:
			tileIndex = idxPowerDot;
			break;
		case Type::Gate:
			tileIndex = idxGate;
			break;
		case Type::Wall:
			tileIndex = 0b1111; // L R T B
			break;
		}
	}
	Type GetType() const { return type; }

private:
	Type type = Type::Undefined;
	const Surface* sprite = nullptr;
	int nColSprite = 0;
	int tileIndex = 0;

	static constexpr int maskL = 0b0001; // 1
	static constexpr int maskR = 0b0010; // 2
	static constexpr int maskT = 0b0100; // 4
	static constexpr int maskB = 0b1000; // 8

	static constexpr int idxFloor = 0;
	static constexpr int idxWallL = 16;
	static constexpr int idxWallR = 17;
	static constexpr int idxWallT = 18;
	static constexpr int idxWallB = 19;
	static constexpr int idxCornerTL = 20;
	static constexpr int idxCornerTR = 21;
	static constexpr int idxCornerBL = 22;
	static constexpr int idxCornerBR = 23;

	static constexpr int idxDot = 24;
	static constexpr int idxPowerDot = 25;
	static constexpr int idxGate = 26;
};