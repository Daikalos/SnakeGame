// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeGameLogic.h"

void ASnakeGameLogic::BeginPlay()
{
	_tilemap = static_cast<ATilemap*>(UGameplayStatics::GetActorOfClass(GetWorld(), ATilemap::StaticClass())); // find tilemap
	_snakePawn = static_cast<ASnakePawn*>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	_tilemap->Initialize(); // control order of calls
	_snakePawn->Initialize(this, _tilemap);

	_foodPos = GetNewFoodPoint();
	_tilemap->SetTile(_foodPos, TileType::Food);
}

int32 ASnakeGameLogic::GetFoodEaten() const noexcept
{
	return _foodEaten;
}

void ASnakeGameLogic::AddFoodEaten()
{
	++_foodEaten;
	_tilemap->SetTile(GetNewFoodPoint(), TileType::Food);
}

bool ASnakeGameLogic::GameOver() const
{
	// game over if outside map, hit body or tail, or reached max size

	return
		!_tilemap->WithinMap(_snakePawn->GetPosition()) ||
		_tilemap->GetTile(_snakePawn->GetPosition()) == TileType::SnakeBody ||
		_tilemap->GetTile(_snakePawn->GetPosition()) == TileType::SnakeTail ||
		_snakePawn->BodySize() == _tilemap->GetWidth() * _tilemap->GetHeight();
}

FIntPoint ASnakeGameLogic::GetNewFoodPoint() const
{
	int32 x{0}, y{0};
	int32 death_spiral = 512; // prevent infinite loop

	do
	{
		x = rand() % _tilemap->GetWidth();
		y = rand() % _tilemap->GetHeight();

		--death_spiral;

	} while (_tilemap->GetTile(x, y) != TileType::Empty && death_spiral >= 0);

	if (death_spiral < 0)
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("Exited with infinite loop"));
	}

	return { x, y };
}