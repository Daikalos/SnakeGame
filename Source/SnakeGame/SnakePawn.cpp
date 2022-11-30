// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakePawn.h"

#include "SnakeGameLogic.h"

// Sets default values
ASnakePawn::ASnakePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_camera = CreateDefaultSubobject<UCameraComponent>(TEXT("UCameraComponent"));
	_camera->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
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

	_camera->SetWorldRotation(FQuat::MakeFromEuler({ 0.0f, 270.0f, -90.0f })); // set rotation and position of camera
	_camera->SetWorldLocation(
		{ 
			_tilemap->GetWidth() * _tilemap->GetTileSize() / 2.0f, 
			_tilemap->GetHeight() * _tilemap->GetTileSize() / 2.0f, 
			_cameraZPos
		});

	_body.Reserve(_length + 1); // +1 for head
	_body.Push(_position); // add head

	_tilemap->SetTile(_position, TileType::SnakeHead);

	for (int32 i = 1; i <= _length; ++i) // create body
	{
		_body.Push(_position - _direction * i);
		_tilemap->SetTile(_body.Last(), TileType::SnakeBody);
	}

	_oldPos = _position;
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
	if (_gameLogic->IsGameOver())
		return;

	if (_tilemap->GetTile(_position) == TileType::Food)
	{
		_gameLogic->AddFoodEaten();

		FIntPoint last = _body.Last();
		_body.Push(last);
	}
	else
	{
		_tilemap->SetTile(_body.Last(), TileType::Empty);
	}

	_tilemap->SetTile(_position, TileType::SnakeHead);
	_tilemap->SetTile(_oldPos, TileType::SnakeBody);

	for (int32 i = _body.Num() - 1; i > 0; --i) // update body
		_body[i] = _body[i - 1];

	_body[0] = _position;

	_tilemap->SetTile(_oldPos, TileType::SnakeBody);
}

void ASnakePawn::MoveLeft()
{
	// TODO: FIX

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

