// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawnBase.h"
#include "Engine/Classes/Camera/CameraComponent.h"
#include "SnakeBase.h"
#include "Components/InputComponent.h"

// Sets default values
APlayerPawnBase::APlayerPawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnCamera = CreateDefaultSubobject<UCameraComponent>("camera");
	RootComponent = PawnCamera;
}

// Вызывается при запуске игры или при появлении
void APlayerPawnBase::BeginPlay()
{
	Super::BeginPlay();
	SetActorRotation(FRotator(-80, 0, 0));
	CreateSnakeActor();
}

// Вызывал каждый кадр
void APlayerPawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Вызывается для привязки функциональности к вводу
void APlayerPawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Vertical", this, &APlayerPawnBase::HandlePlayerVerticalInput);
	PlayerInputComponent->BindAxis("Horizontal", this, &APlayerPawnBase::HandlePlayerHorizontalInput);
}

void APlayerPawnBase::CreateSnakeActor()
{
	SnakeActor = GetWorld()->SpawnActor<ASnakeBase>(SnakeActorClass, FTransform());
}

void APlayerPawnBase::HandlePlayerVerticalInput(float value)
{
	if (IsValid(SnakeActor)) {
		if (value > 0 && SnakeActor->LastMoveDirection != EMovementDirection::DOWN) {
			SnakeActor->LastMoveDirection = EMovementDirection::UP; }
		else if (value < 0 && SnakeActor->LastMoveDirection != EMovementDirection::UP) {
			SnakeActor->LastMoveDirection = EMovementDirection::DOWN; }
	}
}

void APlayerPawnBase::HandlePlayerHorizontalInput(float value)
{
	if (IsValid(SnakeActor)) {
		if (value > 0 && SnakeActor->LastMoveDirection != EMovementDirection::LEFT) {
			SnakeActor->LastMoveDirection = EMovementDirection::RIGHT; }
		else if (value < 0 && SnakeActor->LastMoveDirection != EMovementDirection::RIGHT) { SnakeActor->LastMoveDirection = EMovementDirection::LEFT; }
	}
}

