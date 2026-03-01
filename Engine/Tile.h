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
		Floor,
		Wall,
		PacManSpawn
	};

public:
	Tile() = default;
	Tile(Type type, const Surface* sprite)
		:
		type(type),
		sprite(sprite)
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
			gfx.DrawSprite(gridPos.x * size, gridPos.y * size, rectSpriteTileWall, *sprite, SpriteEffect::Copy{});
			break;
		}
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
	static constexpr RectI rectSpriteTileFloor = {};
	static constexpr RectI rectSpriteTileWall = {};
};