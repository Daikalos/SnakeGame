// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <Kismet/GameplayStatics.h>

#include <vector>
#include <cmath>

#include "Tilemap.h"

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SnakePawn.generated.h"

class ASnakeGameLogic;

UCLASS()
class SNAKEGAME_API ASnakePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASnakePawn();

public:
	const FIntPoint& GetPosition() const;
	int32 BodySize() const;

public:	
	void Initialize(ASnakeGameLogic* gameLogic, ATilemap* tilemap);

	void Tick(float DeltaTime) override;

	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void Update();

	void MoveLeft();
	void MoveRight();
	void MoveDown();
	void MoveUp();

public:
	UPROPERTY(EditAnywhere, meta = (ToolTip = "Speed at which the snake traverses tiles, e.g., speed of 1 means 1 tile per second"))
	float		_tilesPerSecond	{1.0f};

	UPROPERTY(EditAnywhere, meta = (ToolTip = "Current length of the snake"))
	int32		_length			{5};

	UPROPERTY(EditAnywhere, meta = (ToolTip = "Position of the snake"))
	FIntPoint	_position		{8, 5};

	UPROPERTY(EditAnywhere, meta = (ToolTip = "Current direction the snake is heading"))
	FIntPoint	_direction		{1, 0};
	
private:
	float				_moveTimer {0.0f};
	FIntPoint			_oldPos;	// old position to compare if new tile is reached

	TArray<FIntPoint>	_body;		// body of the snake, used primarily to move outmost tail

	ASnakeGameLogic*	_gameLogic	{nullptr};
	ATilemap*			_tilemap	{nullptr};

	friend class ASnakeGameLogic;
};
