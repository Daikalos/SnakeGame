// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakePawn.h"

#include "SnakeGameLogic.h"

// Sets default values
ASnakePawn::ASnakePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

const FIntPoint& ASnakePawn::GetPosition() const
{
	return _position;
}

int32 ASnakePawn::BodySize() const
{
	return _body.Num();
}

void ASnakePawn::Initialize(ASnakeGameLogic* gameLogic, ATilemap* tilemap)
{
	_gameLogic = gameLogic;
	_tilemap = tilemap;

	_moveTimer = _tilesPerSecond;
	_tilesPerSecond /= 1.0f;

	if (!_tilemap->SetTile(_position, TileType::SnakeHead))
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("Failed to set head tile"));
	}

	_body.Reserve(_length + 1);
	_body.Push(_position);

	for (int32 i = 0; i < _length; ++i)
	{
		FIntPoint position = _position + (_direction * (i + 1) * -1);
		_body.Push(position);

		_tilemap->SetTile(position, TileType::SnakeBody);
	}

	_oldPos.X = _position.X;
	_oldPos.Y = _position.Y;
}

// Called every frame
void ASnakePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	_moveTimer -= DeltaTime;

	if (_moveTimer <= 0)
	{
		_position += _direction;

		Update();

		_oldPos = _position;
		_moveTimer = _tilesPerSecond;
	}
}

// Called to bind functionality to input
void ASnakePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("MoveLeft", IE_Pressed, this, &ASnakePawn::MoveLeft);
	PlayerInputComponent->BindAction("MoveRight", IE_Pressed, this, &ASnakePawn::MoveRight);
	PlayerInputComponent->BindAction("MoveDown", IE_Pressed, this, &ASnakePawn::MoveDown);
	PlayerInputComponent->BindAction("MoveUp", IE_Pressed, this, &ASnakePawn::MoveUp);
}

void ASnakePawn::Update()
{
	if (_gameLogic->GameOver())
		return;

	if (_tilemap->GetTile(_position) == TileType::Food)
	{
		_gameLogic->AddFoodEaten();
	}

	_tilemap->SetTile(_position, TileType::SnakeHead);
	_tilemap->SetTile(_oldPos, TileType::SnakeBody);

	int32 l = _body.Num() - 1;
	_tilemap->SetTile(_body[l], TileType::Empty);

	for (int32 i = l; i >= 1; --i) // update body
		_body[i] = _body[i - 1];
}

void ASnakePawn::MoveLeft()
{
	if (_direction.X != 1) // cannot move in on itself
		_direction = { -1, 0 };
}
void ASnakePawn::MoveRight()
{
	if (_direction.X != -1)
		_direction = { 1, 0 };
}
void ASnakePawn::MoveDown()
{
	if (_direction.Y != -1)
		_direction = { 0, 1 };
}
void ASnakePawn::MoveUp()
{
	if (_direction.Y != 1)
		_direction = { 0, -1 };
}

