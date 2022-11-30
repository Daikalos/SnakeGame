// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverWidget.generated.h"

class UTextBlock;
class UButton;

/**
 * 
 */
UCLASS()
class SNAKEGAME_API UGameOverWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void NativeConstruct() override;

	void SetResult(const int32 result);

	UFUNCTION()
	void RestartGame();

	UFUNCTION()
	void QuitGame();

public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextResult;

	UPROPERTY(meta = (BindWidget))
	UButton* ButtonRestartGame;

	UPROPERTY(meta = (BindWidget))
	UButton* ButtonQuitGame;
};
