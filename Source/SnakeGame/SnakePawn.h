// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <Kismet/GameplayStatics.h>

#include <vector>
#include <cmath>

#include "Tilemap.h"

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SnakePawn.generated.h"

UCLASS()
class SNAKEGAME_API ASnakePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASnakePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void NewTileReached();

	void MoveLeft();
	void MoveRight();
	void MoveDown();
	void MoveUp();

public:
	UPROPERTY(EditAnywhere, meta = (ToolTip = "Speed at which the snake traverses tiles, e.g., speed of 1 means 1 tile per second"))
	float		 _speed		{1.0f};

	UPROPERTY(EditAnywhere, meta = (ToolTip = "Current length of the snake"))
	int32		_length		{6};

	UPROPERTY(EditAnywhere, meta = (ToolTip = "Position of the snake"))
	FVector2D	_position	{8, 5};

	UPROPERTY(EditAnywhere, meta = (ToolTip = "Current direction the snake is heading"))
	FIntPoint	_direction	{1, 0};
	
private:
	FIntPoint				_oldPos;	// old position to compare if new tile is reached
	std::vector<FIntPoint>	_body;		// begins with head and ends with tail

	ATilemap*				_tilemap{nullptr}; // reference to tilemap
};
