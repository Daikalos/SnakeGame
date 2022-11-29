// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeGameLogic.h"

void ASnakeGameLogic::BeginPlay()
{

}

void ASnakeGameLogic::SetTilemap(ATilemap* const tilemap)
{
	_tilemap = tilemap;
}
ATilemap* ASnakeGameLogic::GetTilemap() const noexcept
{
	return _tilemap;
}