// Fill out your copyright notice in the Description page of Project Settings.

#include "JeJoOpenDoor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"

void UJeJoOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	DoorOpenAngle += InitialYaw;

	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("No pressureplate set for: %s !"), *(GetOwner()->GetName()));
	}
	// set the actor that opens (i.e. Door)
	ActorThatOpen = GetWorld()->GetFirstPlayerController()->GetPawn();
}

// sets default values for this component's properties
UJeJoOpenDoor::UJeJoOpenDoor()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UJeJoOpenDoor::TickComponent(float deltaTime, ELevelTick tickType, FActorComponentTickFunction* thisTickFunction)
{
	Super::TickComponent(deltaTime, tickType, thisTickFunction);

	// trigger an action
	if (PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpen))
	{
		OpenDoor(deltaTime);
		DoorLastOpen = GetWorld()->GetTimeSeconds();
	}
	else
	{
		if (GetWorld()->GetTimeSeconds() - DoorLastOpen > DoorCloseDelay)
		{
			CloseDoor(deltaTime);
		}
	}
}

void UJeJoOpenDoor::OpenDoor(const float DeltaTime) noexcept
{
	// debug log message
	// UE_LOG(LogTemp, Warning, TEXT("%s"), *(GetOwner()->GetActorRotation().ToString()));
	// UE_LOG(LogTemp, Warning, TEXT("Yaw: %f"), GetOwner()->GetActorRotation().Yaw);

	// rotate from the current door position
	CurrentYaw = FMath::Lerp(CurrentYaw, DoorOpenAngle, DeltaTime * DoorOpenSpeed);
	FRotator RotateDoor{GetOwner()->GetActorRotation()};
	RotateDoor.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(RotateDoor);
}

void UJeJoOpenDoor::CloseDoor(const float DeltaTime) noexcept
{
	// UE_LOG(LogTemp, Warning, TEXT("%s"), *(GetOwner()->GetActorRotation().ToString()));
	// UE_LOG(LogTemp, Warning, TEXT("Yaw: %f"), GetOwner()->GetActorRotation().Yaw);

	// rotate from the current door position
	CurrentYaw = FMath::Lerp(CurrentYaw, InitialYaw, DeltaTime * DoorCloseSpeed);
	FRotator RotateDoor{GetOwner()->GetActorRotation()};
	RotateDoor.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(RotateDoor);
}
