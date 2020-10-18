// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "Engine/TriggerVolume.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "JeJoOpenDoor.h"

DEFINE_LOG_CATEGORY(LogJeJoOpenDoor)

void UJeJoOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	// set the initial values
	this->initialYaw = this->currentYaw = GetOwner()->GetActorRotation().Yaw;
	this->targetAngle += this->initialYaw;

	// log messages
	UE_LOG(LogJeJoOpenDoor, Log, TEXT("this->initialYaw: %f"), this->initialYaw);
	UE_LOG(LogJeJoOpenDoor, Log, TEXT("this->currentYaw: %f"), this->currentYaw);
	UE_LOG(LogJeJoOpenDoor, Log, TEXT("this->targetAngle: %f"), this->targetAngle);

	if (!this->pressurePlate)
	{
		UE_LOG(LogJeJoOpenDoor, Error, TEXT("No pressure-plate set for: %s!"), *(GetOwner()->GetName()));
	}

	// set the actor that opens (i.e. Door)
	this->playerActor = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!this->playerActor)
	{
		UE_LOG(LogJeJoOpenDoor, Error, TEXT("No player pawn found!"));
	}
}

// sets default values for this component's properties
UJeJoOpenDoor::UJeJoOpenDoor()
	: initialYaw{ 0.f }
	, currentYaw{ 0.f }
	, lastOpenTime{ 0.f }
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UJeJoOpenDoor::TickComponent(
	float deltaTime, ELevelTick tickType, FActorComponentTickFunction* thisTickFunction)
{
	Super::TickComponent(deltaTime, tickType, thisTickFunction);

	const UWorld *const world = GetWorld();
	const AActor *const ownerActor = GetOwner();

	// component works only if world and the owner actor exists\n
	// and the actor overlaps the trigger volume
	if (world && ownerActor && this->pressurePlate && this->playerActor &&
		this->pressurePlate->IsOverlappingActor(this->playerActor))
	{
		this->OpenDoor(deltaTime);
		this->lastOpenTime = world->GetTimeSeconds();
	}
	else if (world && ownerActor && this->pressurePlate && this->playerActor &&
		(world->GetTimeSeconds() - this->lastOpenTime) > this->delayTime)
	{
		this->CloseDoor(deltaTime);
	}
}

void UJeJoOpenDoor::OpenDoor(const float deltaTime) noexcept
{
	if (AActor *const ownerActor = GetOwner())
	{
		// debug log message
		// UE_LOG(LogJeJoOpenDoor, Warning, TEXT("%s"), *(actor->GetActorRotation().ToString()));
		// UE_LOG(LogJeJoOpenDoor, Warning, TEXT("Yaw: %f"), actor->GetActorRotation().Yaw);

		// rotate from the current door position to target door opening angle
		FRotator rotateDoor{ ownerActor->GetActorRotation() };
		rotateDoor.Yaw = this->currentYaw
			= FMath::FInterpTo(this->currentYaw, this->targetAngle, deltaTime, this->openingSpeed);
		ownerActor->SetActorRotation(MoveTemp(rotateDoor));
	}
}

void UJeJoOpenDoor::CloseDoor(const float deltaTime) noexcept
{
	if (AActor *const ownerActor = GetOwner())
	{
		// debug log message
		// UE_LOG(LogJeJoOpenDoor, Warning, TEXT("%s"), *(actor->GetActorRotation().ToString()));
		// UE_LOG(LogJeJoOpenDoor, Warning, TEXT("Yaw: %f"), actor->GetActorRotation().Yaw);

		// rotate from the current door position to the initial position
		FRotator rotateDoor{ ownerActor->GetActorRotation() };
		rotateDoor.Yaw = this->currentYaw
			= FMath::FInterpTo(this->currentYaw, this->initialYaw, deltaTime, this->closingSpeed);
		ownerActor->SetActorRotation(MoveTemp(rotateDoor));
	}
}
