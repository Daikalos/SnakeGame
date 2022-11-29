// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tilemap.h"
#include "SnakePawn.h"

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
	void SetTilemap(ATilemap* const tilemap);
	ATilemap* GetTilemap() const noexcept;

private:
	ATilemap* _tilemap {nullptr}; // hold reference to tilemap to allow for snake pawn to easily access it
};
