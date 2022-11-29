// Fill out your copyright notice in the Description page of Project Settings.

#include "Tilemap.h"
#include "ProceduralMeshComponent.h"

// Sets default values
ATilemap::ATilemap() : _tiles(std::make_unique<TileType[]>(_width * _height))
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProceduralMesh"));
	_mesh->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ATilemap::BeginPlay()
{
	Super::BeginPlay();

	for (int32 y = 0; y < _height; ++y)
		for (int32 x = 0; x < _width; ++x)
		{
			//_mesh->CreateMeshSection(0,)
		}
}

bool ATilemap::WithinMap(const int32 x, const int32 y) const
{
	return !(x < 0 || y < 0 || x >= _width || y >= _height);
}

TileType ATilemap::GetTile(const int32 x, const int32 y) const
{
	if (!WithinMap(x, y))
		return TileType::Empty;

	return _tiles[IX(x, y)];
}
bool ATilemap::SetTile(const int32 x, const int32 y, const TileType tile_type)
{
	if (!WithinMap(x, y))
		return false;

	_tiles[IX(x, y)] = tile_type;

	return true;
}

void ATilemap::UpdateTileTexture(const int32 x, const int32 y, const TileType tile_type)
{
	const int32 index = IX(x, y);

	switch (tile_type)
	{
	case TileType::Empty:

		break;
	case TileType::Food:

		break;
	case TileType::SnakeBody:

		break;
	case TileType::SnakeHead:

		break;
	case TileType::SnakeTail:

		break;
	default: 
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("Unknown tile type"));
		break;
	}
}

constexpr int32 ATilemap::IX(const int32 x, const int32 y) const noexcept
{
	return x + y * _width;
}

