// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <memory>

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tilemap.generated.h"

UENUM(BlueprintType)
enum class TileType : uint8
{
	Empty		UMETA(DisplayName = "Empty"),
	Food		UMETA(DisplayName = "Food"),
	SnakeBody	UMETA(DisplayName = "SnakeBody"),
	SnakeHead	UMETA(DisplayName = "SnakeHead"),
	SnakeTail	UMETA(DisplayName = "SnakeTail")
};

class UProceduralMeshComponent;

UCLASS()
class SNAKEGAME_API ATilemap : public AActor
{
	GENERATED_BODY()

public:
	using TilePtr = std::unique_ptr<TileType[]>;
	
public:	
	// Sets default values for this actor's properties
	ATilemap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	bool WithinMap(const int32 x, const int32 y) const;

	TileType GetTile(const int32 x, const int32 y) const;
	bool SetTile(const int32 x, const int32 y, const TileType tile_type);

private:
	// Updates the texture for a tile dependant on the passed tile type
	//
	void UpdateTileTexture(const int32 x, const int32 y, const TileType tile_type);

	// Converts 2D coordinate to index in array
	//
	constexpr int32 IX(const int32 x, const int32 y) const noexcept;

public:
	UPROPERTY(EditAnywhere)
	uint16	_width		{12};	// number of tiles in width

	UPROPERTY(EditAnywhere)
	uint16	_height		{9};	// number of tiles in height

	UPROPERTY(EditAnywhere)
	uint16	_tileSize	{128};	// size of each tile in the grid

private:
	TilePtr _tiles;

	UProceduralMeshComponent* _mesh {nullptr}; // mesh of the grid
};
