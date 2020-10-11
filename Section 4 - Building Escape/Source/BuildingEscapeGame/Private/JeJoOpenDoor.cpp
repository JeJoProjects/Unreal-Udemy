// Fill out your copyright notice in the Description page of Project Settings.

#include "JeJoOpenDoor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"

DEFINE_LOG_CATEGORY(LogJeJoOpenDoor)

void UJeJoOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	this->initialYaw = GetOwner()->GetActorRotation().Yaw;
	this->currentYaw = this->initialYaw;
	this->doorOpenAngle += this->initialYaw;

	if (!pressurePlate)
	{
		UE_LOG(LogJeJoOpenDoor, Error, TEXT("No pressure-plate set for: %s !"), *(GetOwner()->GetName()));
	}
	// set the actor that opens (i.e. Door)
	this->actorThatOpen = GetWorld()->GetFirstPlayerController()->GetPawn();
}

// sets default values for this component's properties
UJeJoOpenDoor::UJeJoOpenDoor()
	: initialYaw{ 0.f }
	, currentYaw{ 0.f }
	, doorLastOpen{ 0.f }
	, doorOpenAngle{ 270.f }
	, doorOpenSpeed{ 2.f }
	, doorCloseSpeed{ 0.8f }
	, doorCloseDelay{ 20.f }
	, pressurePlate{ nullptr }
	, actorThatOpen{ nullptr }
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UJeJoOpenDoor::TickComponent(
	float deltaTime, ELevelTick tickType, FActorComponentTickFunction* thisTickFunction)
{
	Super::TickComponent(deltaTime, tickType, thisTickFunction);

	// trigger an action
	if (this->pressurePlate && this->pressurePlate->IsOverlappingActor(this->actorThatOpen))
	{
		OpenDoor(deltaTime);
		this->doorLastOpen = GetWorld()->GetTimeSeconds();
	}
	else
	{
		if (GetWorld()->GetTimeSeconds() - this->doorLastOpen > this->doorCloseDelay)
		{
			CloseDoor(deltaTime);
		}
	}
}

void UJeJoOpenDoor::OpenDoor(const float DeltaTime) noexcept
{
	// debug log message
	UE_LOG(LogJeJoOpenDoor, Warning, TEXT("%s"), *(GetOwner()->GetActorRotation().ToString()));
	UE_LOG(LogJeJoOpenDoor, Warning, TEXT("Yaw: %f"), GetOwner()->GetActorRotation().Yaw);

	// rotate from the current door position
	this->currentYaw = FMath::Lerp(this->currentYaw, this->doorOpenAngle, DeltaTime * this->doorOpenSpeed);
	FRotator RotateDoor{GetOwner()->GetActorRotation()};
	RotateDoor.Yaw = this->currentYaw;
	GetOwner()->SetActorRotation(RotateDoor);
}

void UJeJoOpenDoor::CloseDoor(const float DeltaTime) noexcept
{
	UE_LOG(LogJeJoOpenDoor, Warning, TEXT("%s"), *(GetOwner()->GetActorRotation().ToString()));
	UE_LOG(LogJeJoOpenDoor, Warning, TEXT("Yaw: %f"), GetOwner()->GetActorRotation().Yaw);

	// rotate from the current door position
	this->currentYaw = FMath::Lerp(this->currentYaw, initialYaw, DeltaTime * this->doorCloseSpeed);
	FRotator RotateDoor{GetOwner()->GetActorRotation()};
	RotateDoor.Yaw = this->currentYaw;
	GetOwner()->SetActorRotation(RotateDoor);
}
