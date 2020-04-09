// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"

void UOpenDoor::BeginPlay()
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
UOpenDoor::UOpenDoor()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// trigger an action
	if (PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpen))
	{
		OpenDoor(DeltaTime);
		DoorLastOpen = GetWorld()->GetTimeSeconds();
	}
	else
	{
		if (GetWorld()->GetTimeSeconds() - DoorLastOpen > DoorCloseDelay)
		{
			CloseDoor(DeltaTime);
		}
	}
}

void UOpenDoor::OpenDoor(const float DeltaTime) noexcept
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

void UOpenDoor::CloseDoor(const float DeltaTime) noexcept
{
	// UE_LOG(LogTemp, Warning, TEXT("%s"), *(GetOwner()->GetActorRotation().ToString()));
	// UE_LOG(LogTemp, Warning, TEXT("Yaw: %f"), GetOwner()->GetActorRotation().Yaw);

	// rotate from the current door position
	CurrentYaw = FMath::Lerp(CurrentYaw, InitialYaw, DeltaTime * DoorCloseSpeed);
	FRotator RotateDoor{GetOwner()->GetActorRotation()};
	RotateDoor.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(RotateDoor);
}
