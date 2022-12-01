// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SnakeGameLogic.generated.h"

class UPlayerHUDWidget;
class UGameOverWidget;

class ATilemap;
class ASnakePawn;

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
	void AddFoodEaten();
	bool IsGameOver();

private:
	FIntPoint GetNewApplePos() const;

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<UPlayerHUDWidget> PlayerHUDWidget = nullptr;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<UGameOverWidget> GameOverWidget = nullptr;

private:
	int32		_applesEaten {0};
	FIntPoint	_applePos;

	UPlayerHUDWidget*	_playerHUDWidget	{nullptr};
	UGameOverWidget*	_gameOverWidget		{nullptr};

	ATilemap*			_tilemap			{nullptr};
	ASnakePawn*			_snakePawn			{nullptr};
};
