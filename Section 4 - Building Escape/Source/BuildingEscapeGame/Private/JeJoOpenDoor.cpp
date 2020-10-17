// Fill out your copyright notice in the Description page of Project Settings.

#include "JeJoOpenDoor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"

DEFINE_LOG_CATEGORY(LogJeJoOpenDoor)

void UJeJoOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	// set the initial values
	this->initialYaw = this->currentYaw = GetOwner()->GetActorRotation().Yaw;
	this->doorOpenAngle += this->initialYaw;

	// log messages
	UE_LOG(LogJeJoOpenDoor, Log, TEXT("this->initialYaw: %f"), this->initialYaw);
	UE_LOG(LogJeJoOpenDoor, Log, TEXT("this->currentYaw: %f"), this->currentYaw);
	UE_LOG(LogJeJoOpenDoor, Log, TEXT("this->doorOpenAngle: %f"), this->doorOpenAngle);

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
	, doorOpenAngle{ 90.f }
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

	UWorld* world = GetWorld();
	AActor* actor = GetOwner();

	// component works only if world and the owner actor exists.
	if (world && actor)
	{
		this->OpenDoor(deltaTime);
		this->doorLastOpen = world->GetTimeSeconds();
	}
#if 0
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
#endif
}

void UJeJoOpenDoor::OpenDoor(const float deltaTime) noexcept
{
	if (AActor* actor = GetOwner())
	{
		// debug log message
		// UE_LOG(LogJeJoOpenDoor, Warning, TEXT("%s"), *(actor->GetActorRotation().ToString()));
		// UE_LOG(LogJeJoOpenDoor, Warning, TEXT("Yaw: %f"), actor->GetActorRotation().Yaw);

		// rotate from the current door position
		FRotator rotateDoor{ actor->GetActorRotation() };
		rotateDoor.Yaw = this->currentYaw
			= FMath::FInterpTo(this->currentYaw, this->doorOpenAngle, deltaTime, this->doorOpenSpeed);
		actor->SetActorRotation(MoveTemp(rotateDoor));
	}
}

void UJeJoOpenDoor::CloseDoor(const float deltaTime) noexcept
{
	UE_LOG(LogJeJoOpenDoor, Warning, TEXT("%s"), *(GetOwner()->GetActorRotation().ToString()));
	UE_LOG(LogJeJoOpenDoor, Warning, TEXT("Yaw: %f"), GetOwner()->GetActorRotation().Yaw);

	// rotate from the current door position
	this->currentYaw = FMath::FInterpTo(this->currentYaw, initialYaw, deltaTime, this->doorCloseSpeed);
	FRotator RotateDoor{GetOwner()->GetActorRotation()};
	RotateDoor.Yaw = this->currentYaw;
	GetOwner()->SetActorRotation(RotateDoor);
}
