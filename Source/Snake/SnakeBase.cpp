// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeBase.h"
#include "SnakeElementBase.h"

// Sets default values
ASnakeBase::ASnakeBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ElementSize = 100.f;
	MovementSpeed = 10.f;
	LastMoveDirection = EMovementDirection::DOWN;
}

// Called when the game starts or when spawned
void ASnakeBase::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickInterval(MovementSpeed);
	AddSnakeElement(4);
	
}

// Called every frame
void ASnakeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move();
}

void ASnakeBase::AddSnakeElement(int ElemrntsNum)
{
	for (int i = 0; i < ElemrntsNum; ++i) {
		FVector NewLocation(SnakeElements.Num() * ElementSize, 0, 0);
		FTransform NewTransform(NewLocation);
		ASnakeElementBase* NewSnakeElement = GetWorld()->SpawnActor<ASnakeElementBase>(SnakeElementClass, NewTransform);
		int32 ElemIndex = SnakeElements.Add(NewSnakeElement);
		if (ElemIndex == 0) { NewSnakeElement->SetFirstElementType(); }
	}
}

void ASnakeBase::Move()
{
	FVector MovementVector;
	float MovementSpeed2 = ElementSize;

	
	switch (LastMoveDirection)
	{
	case EMovementDirection::UP:
		MovementVector.X += MovementSpeed2;
		break;
	case EMovementDirection::DOWN:
		MovementVector.X -= MovementSpeed2;
		break;
	case EMovementDirection::LEFT:
		MovementVector.Y += MovementSpeed2;
		break;
	case EMovementDirection::RIGHT:
		MovementVector.Y -= MovementSpeed2;
		break;
	}

	//AddActorWorldOffset(MovementVector);

	for (int i = SnakeElements.Num() - 1; i > 0; i--) {
		auto CurrentElement = SnakeElements[i];
		auto PrevElement = SnakeElements[i - 1];
		FVector PrevLocation = PrevElement->GetActorLocation();
		CurrentElement->SetActorLocation(PrevLocation);
	}

	SnakeElements[0]->AddActorWorldOffset(MovementVector);
}

