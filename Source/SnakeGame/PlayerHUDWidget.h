// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUDWidget.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class SNAKEGAME_API UPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetApples(const int32 apples);

public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextApples;
};
