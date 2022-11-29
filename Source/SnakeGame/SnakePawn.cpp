// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakePawn.h"

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
	
}

// Called every frame
void ASnakePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	_position += FVector2D(_direction) * _speed;
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

