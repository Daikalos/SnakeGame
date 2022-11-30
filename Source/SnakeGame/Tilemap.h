// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <Kismet/GameplayStatics.h>

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

	Count // keep this at end
};

class UProceduralMeshComponent;
class UMaterialInterface;
class ATilemap;

// match tiletype to specific color
//
static const FColor TileColor[] =
{
	FColor(10, 40, 10), // Empty
	FColor(255, 0, 0),	// Food
	FColor(0, 255, 0),	// Body
	FColor(0, 75, 0),	// Head
};

class Tile
{
public:
	Tile() = default;
	Tile(TileType tileType, const FIntPoint& position, int32 index, int32 tileSize);

	bool operator==(const TileType& rhs) const;
	bool operator!=(const TileType& rhs) const;

public:
	const TileType& GetType() const noexcept;

public:
	// Sets the type and updates the color for a tile dependant on the passed tile type
	//
	void SetType(TileType tileType);

	void BuildMesh(UProceduralMeshComponent* const mesh, UMaterialInterface* const mtl);
	void UpdateMesh(UProceduralMeshComponent* const mesh);

private:
	TileType			_tileType	{TileType::Empty};
	FIntPoint			_position;
	int32				_index		{0};
	int32				_tileSize	{0};

	TArray<FVector>		_vertices;
	TArray<int32>		_triangles;
	TArray<FColor>		_color;

	friend ATilemap;
};

UCLASS()
class SNAKEGAME_API ATilemap : public AActor
{
	GENERATED_BODY()

private:
	using TileArrayPtr = std::unique_ptr<Tile[]>;
	
public:	
	// Sets default values for this actor's properties
	ATilemap();

public:
	void Initialize();

public:
	[[nodiscard]] constexpr int32 GetWidth() const noexcept;
	[[nodiscard]] constexpr int32 GetHeight() const noexcept;
	[[nodiscard]] constexpr int32 GetTileSize() const noexcept;

	[[nodiscard]] const Tile& GetTile(const int32 x, const int32 y) const;
	bool SetTile(const int32 x, const int32 y, const TileType tileType);

	[[nodiscard]] const Tile& GetTile(const FIntPoint& point) const;
	bool SetTile(const FIntPoint& point, const TileType tileType);

	// returns true if the given coordinates is within the borders of the tilemap
	//
	[[nodiscard]] bool WithinMap(const int32 x, const int32 y) const;
	[[nodiscard]] bool WithinMap(const FIntPoint& point) const;

private:
	// Converts 2D coordinate to index in array
	//
	[[nodiscard]] constexpr int32 IX(const int32 x, const int32 y) const noexcept;

public:
	UPROPERTY(EditAnywhere)
	int32	_width		{30};	// number of tiles in width

	UPROPERTY(EditAnywhere)
	int32	_height		{15};	// number of tiles in height

	UPROPERTY(EditAnywhere)
	int32	_tileSize	{64};	// size of each tile in the grid

	UPROPERTY(EditAnywhere)
	UMaterialInterface* _material {nullptr};

private:
	TileArrayPtr _tiles;

	UProceduralMeshComponent*	_mesh		{nullptr}; // mesh of the grid
};
