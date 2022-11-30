// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUDWidget.h"

#include <Components/TextBlock.h>

void UPlayerHUDWidget::SetApples(const int32 apples)
{
	TextApples->SetText(FText::FromString("Apples: " + FString::FromInt(apples)));
}