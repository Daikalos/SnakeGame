// Fill out your copyright notice in the Description page of Project Settings.

#include "Tilemap.h"

#include "ProceduralMeshComponent.h"
#include "SnakeGameLogic.h"

// -- tile --

Tile::Tile(TileType tileType, const FIntPoint& position, int32 index, int32 tileSize)
	: _tileType(), _position(position), _index(index), _tileSize(tileSize)
{
	SetType(tileType);

	_vertices.Add(FVector(	 position.X * tileSize,			 position.Y * tileSize,			0));
	_vertices.Add(FVector(	 position.X * tileSize,			(position.Y + 1) * tileSize,	0));
	_vertices.Add(FVector(	(position.X + 1) * tileSize,	 position.Y * tileSize,			0));
	_vertices.Add(FVector(	(position.X + 1) * tileSize,	(position.Y + 1) * tileSize,	0));

	_triangles.Add(0);
	_triangles.Add(1);
	_triangles.Add(2);
	_triangles.Add(1);
	_triangles.Add(3);
	_triangles.Add(2);
}

bool Tile::operator==(const TileType& rhs) const
{
	return _tileType == rhs;
}
bool Tile::operator!=(const TileType& rhs) const
{
	return !(*this == rhs);
}

const TileType& Tile::GetType() const noexcept
{
	return _tileType;
}

void Tile::SetType(TileType tileType)
{
	_tileType = tileType;

	int32 typeIndex = (int32)_tileType;
	const FLinearColor& color = TileColor[typeIndex];

	if (_color.Num())
	{
		_color[0] = color;
		_color[1] = color;
		_color[2] = color;
		_color[3] = color;
	}
	else
	{
		_color.Add(color);
		_color.Add(color);
		_color.Add(color);
		_color.Add(color);
	}
}

void Tile::BuildMesh(UProceduralMeshComponent* const mesh, UMaterialInterface* const mtl)
{
	mesh->CreateMeshSection_LinearColor(_index, _vertices, _triangles, TArray<FVector>(), TArray<FVector2D>(), _color, TArray<FProcMeshTangent>(), false);
	mesh->SetMaterial(_index, mtl);
}

void Tile::UpdateMesh(UProceduralMeshComponent* const mesh)
{
	mesh->UpdateMeshSection_LinearColor(_index, _vertices, TArray<FVector>(), TArray<FVector2D>(), _color, TArray<FProcMeshTangent>());
}

// -- tilemap --

ATilemap::ATilemap() : _tiles(std::make_unique<Tile[]>(_width * _height))
{
	PrimaryActorTick.bCanEverTick = false;

	_mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProceduralMesh"));
	_mesh->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
}

void ATilemap::Initialize()
{
	for (int32 y = 0; y < _height; ++y)
		for (int32 x = 0; x < _width; ++x)
		{
			int32 i = IX(x, y);

			Tile& tile = (_tiles[i] = Tile(TileType::Empty, { x, y }, i, _tileSize));
			tile.BuildMesh(_mesh, _material);
		}
}

constexpr uint16 ATilemap::GetWidth() const noexcept
{
	return _width;
}
constexpr uint16 ATilemap::GetHeight() const noexcept
{
	return _height;
}

const Tile& ATilemap::GetTile(const int32 x, const int32 y) const
{
	return _tiles[IX(x, y)];
}
bool ATilemap::SetTile(const int32 x, const int32 y, const TileType tile_type)
{
	if (!WithinMap(x, y))
		return false;

	Tile& tile = _tiles[IX(x, y)];

	tile.SetType(tile_type);
	tile.UpdateMesh(_mesh);

	return true;
}

const Tile& ATilemap::GetTile(const FIntPoint& point) const
{
	return GetTile(point.X, point.Y);
}
bool ATilemap::SetTile(const FIntPoint& point, const TileType tile_type)
{
	return SetTile(point.X, point.Y, tile_type);
}

bool ATilemap::WithinMap(const int32 x, const int32 y) const
{
	return !(x < 0 || y < 0 || x >= _width || y >= _height);
}
bool ATilemap::WithinMap(const FIntPoint& point) const
{
	return WithinMap(point.X, point.Y);
}

constexpr int32 ATilemap::IX(const int32 x, const int32 y) const noexcept
{
	return x + y * _width;
}

