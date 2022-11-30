// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeGameLogic.h"

#include <Kismet/GameplayStatics.h>

#include "PlayerHUDWidget.h"
#include "GameOverWidget.h"

#include "Tilemap.h"
#include "SnakePawn.h"

void ASnakeGameLogic::BeginPlay()
{
	_tilemap = static_cast<ATilemap*>(UGameplayStatics::GetActorOfClass(GetWorld(), ATilemap::StaticClass())); // find tilemap
	_snakePawn = static_cast<ASnakePawn*>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	_tilemap->Initialize(); // control order of calls
	_snakePawn->Initialize(this, _tilemap);

	_foodPos = GetNewFoodPoint();
	_tilemap->SetTile(_foodPos, TileType::Food);

	auto controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	_playerHUDWidget = CreateWidget<UPlayerHUDWidget>(controller, PlayerHUDWidget);
	_playerHUDWidget->AddToViewport(9999);

	controller->SetInputMode(FInputModeGameOnly());
	controller->SetShowMouseCursor(false);
}

int32 ASnakeGameLogic::GetFoodEaten() const noexcept
{
	return _foodEaten;
}

void ASnakeGameLogic::AddFoodEaten()
{
	++_foodEaten;

	_playerHUDWidget->SetApples(_foodEaten);
	_tilemap->SetTile(GetNewFoodPoint(), TileType::Food);
}

bool ASnakeGameLogic::IsGameOver()
{
	// game over if outside map, hit body or tail, or reached max size

	const bool gameOver = !_tilemap->WithinMap(_snakePawn->GetPosition()) ||
		_tilemap->GetTile(_snakePawn->GetPosition()) == TileType::SnakeBody ||
		_snakePawn->BodySize() == _tilemap->GetWidth() * _tilemap->GetHeight();

	if (gameOver)
	{
		_playerHUDWidget->RemoveFromParent();

		auto controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);

		_gameOverWidget = CreateWidget<UGameOverWidget>(controller, GameOverWidget);
		_gameOverWidget->AddToViewport(9999);

		_gameOverWidget->SetResult(_foodEaten);

		controller->SetShowMouseCursor(true);
		controller->SetInputMode(FInputModeGameAndUI());

		controller->Pause();
	}

	return gameOver;
}

FIntPoint ASnakeGameLogic::GetNewFoodPoint() const
{
	// This works well enough, but as the snake grows and there are less tiles
	// available, this leads to decrease in performance as it attempts to 
	// find an available tile.

	int32 x{0}, y{0};
	int32 deathSpiral = 4096; // prevent infinite loop

	do
	{
		x = rand() % _tilemap->GetWidth();
		y = rand() % _tilemap->GetHeight();

		--deathSpiral;

	} while (_tilemap->GetTile(x, y) != TileType::Empty && deathSpiral >= 0);

	if (deathSpiral < 0)
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("Exited with infinite loop"));
	}

	return { x, y };
}