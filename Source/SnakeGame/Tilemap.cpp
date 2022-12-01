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

	int32 typeIndex = (int32)_tileType;
	const FColor& color = TileColor[typeIndex];

	_color.Add(color);
	_color.Add(color);
	_color.Add(color);
	_color.Add(color);
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
	const FColor& color = TileColor[typeIndex];

	for (FColor& c : _color) // update the color
		c = color;
}

void Tile::BuildMesh(UProceduralMeshComponent* const mesh, UMaterialInterface* const mtl)
{
	// Creating a separate mesh for each tile is usually not a good idea since 
	// it could affect performance significantly if the grid was very large.
	//
	// But given the context, and in order to quickly and easily update the mesh 
	// when a tile updated, I think this solution works well enough.

	mesh->CreateMeshSection(_index, _vertices, _triangles, TArray<FVector>(), TArray<FVector2D>(), _color, TArray<FProcMeshTangent>(), false);
	mesh->SetMaterial(_index, mtl);
}

void Tile::UpdateMesh(UProceduralMeshComponent* const mesh)
{
	mesh->UpdateMeshSection(_index, _vertices, TArray<FVector>(), TArray<FVector2D>(), _color, TArray<FProcMeshTangent>());
}

// -- tilemap --

ATilemap::ATilemap()
{
	PrimaryActorTick.bCanEverTick = false;

	_mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProceduralMesh"));
	_mesh->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
}

void ATilemap::Initialize()
{
	_tiles = std::make_unique<Tile[]>(_width * _height);

	for (int32 y = 0; y < _height; ++y)
		for (int32 x = 0; x < _width; ++x) // create the grid
		{
			int32 i = IX(x, y);

			Tile& tile = (_tiles[i] = Tile(TileType::Empty, { x, y }, i, _tileSize));
			tile.BuildMesh(_mesh, _material);
		}
}

const int32& ATilemap::GetWidth() const noexcept
{
	return _width;
}
const int32& ATilemap::GetHeight() const noexcept
{
	return _height;
}
const int32& ATilemap::GetTileSize() const noexcept
{
	return _tileSize;
}

const Tile& ATilemap::GetTile(const int32 x, const int32 y) const
{
	return _tiles[IX(x, y)];
}
bool ATilemap::SetTile(const int32 x, const int32 y, const TileType tileType)
{
	if (!WithinMap(x, y))
		return false;

	Tile& tile = _tiles[IX(x, y)];

	if (tile != tileType) // set new tile and update mesh for new color if new
	{
		tile.SetType(tileType);
		tile.UpdateMesh(_mesh); 
	}

	return true;
}

const Tile& ATilemap::GetTile(const FIntPoint& point) const
{
	return GetTile(point.X, point.Y);
}
bool ATilemap::SetTile(const FIntPoint& point, const TileType tileType)
{
	return SetTile(point.X, point.Y, tileType);
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

