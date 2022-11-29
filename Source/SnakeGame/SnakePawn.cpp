// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakePawn.h"

#include "SnakeGameLogic.h"

// Sets default values
ASnakePawn::ASnakePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASnakePawn::BeginPlay()
{
	Super::BeginPlay();
	
	_tilemap = static_cast<ASnakeGameLogic*>(UGameplayStatics::GetGameMode(GetWorld()))->GetTilemap(); // get the tilemap
}

// Called every frame
void ASnakePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	_position += FVector2D(_direction) * _speed * DeltaTime;

	const int32 x = (int32)_position.X; // floor x and y
	const int32 y = (int32)_position.Y;

	if (x != _oldPos.X || y != _oldPos.Y)
		NewTileReached(x, y);

	_oldPos.X = x;
	_oldPos.Y = y;
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

void ASnakePawn::NewTileReached(const int32 x, const int32 y)
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("Test"));
}

void ASnakePawn::MoveLeft()
{
	_direction = { -1, 0 };
}
void ASnakePawn::MoveRight()
{
	_direction = { 1, 0 };
}
void ASnakePawn::MoveDown()
{
	_direction = { 0, 1 };
}
void ASnakePawn::MoveUp()
{
	_direction = { 0, -1 };
}

