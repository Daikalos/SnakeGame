// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverWidget.h"

#include <Kismet/GameplayStatics.h>

#include <Components/TextBlock.h>
#include <Components/Button.h>

void UGameOverWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ButtonRestartGame->OnClicked.AddDynamic(this, &UGameOverWidget::RestartGame);
	ButtonQuitGame->OnClicked.AddDynamic(this, &UGameOverWidget::QuitGame);
}

void UGameOverWidget::SetResult(const int32 result)
{
	TextResult->SetText(FText::FromString("You got " + FString::FromInt(result) + " apples!"));
}

void UGameOverWidget::RestartGame()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false); // just reloads the level
}
void UGameOverWidget::QuitGame()
{
	FGenericPlatformMisc::RequestExit(false);
}