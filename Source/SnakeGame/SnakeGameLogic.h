// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tilemap.h"
#include "SnakePawn.h"

#include <Kismet/GameplayStatics.h>

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SnakeGameLogic.generated.h"

/**
 * 
 */
UCLASS()
class SNAKEGAME_API ASnakeGameLogic : public AGameModeBase
{
	GENERATED_BODY()
	
private:
	void BeginPlay() override;

public:
	int32 GetFoodEaten() const noexcept;
	void AddFoodEaten();

	bool GameOver() const;

private:
	FIntPoint GetNewFoodPoint() const;

private:
	int32		_foodEaten	{0};
	FIntPoint	_foodPos;

	ATilemap*	_tilemap	{nullptr}; // hold reference to tilemap to allow for snake pawn to easily access it
	ASnakePawn* _snakePawn	{nullptr};
};
