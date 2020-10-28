/****************************************************************************************
 * Open door component implementation.
 *
 * @Authur : JJ
 * @license: MIT
****************************************************************************************/
#include "Engine/World.h"
#include "Engine/TriggerVolume.h"
#include "Components/PrimitiveComponent.h"
#include "Components/AudioComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "JeJoOpenDoor.h"

DEFINE_LOG_CATEGORY(LogJeJoOpenDoor)

// sets default values for this component's properties
UJeJoOpenDoor::UJeJoOpenDoor()
	: initialYaw{ 0.f }
	, currentYaw{ 0.f }
	, lastOpenTime{ 0.f }
	, isOpenDoorSoundPlaying{ false }
	, isCloseDoorSoundPlaying{ true }
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UJeJoOpenDoor::TickComponent(
	float deltaTime, ELevelTick tickType, FActorComponentTickFunction* thisTickFunction)
{
	Super::TickComponent(deltaTime, tickType, thisTickFunction);

	const UWorld *const world = GetWorld();
	const AActor *const ownerActor = GetOwner();

	// OLD Concept: component works only if world and the owner actor exists\n
	// and the actor overlaps the trigger volume
	// if (world && ownerActor && this->pressurePlate && this->playerActor &&
	// 	this->pressurePlate->IsOverlappingActor(this->playerActor))
	if(this->massToOpenDoor < this->GetTotalOverlappingActorsMass())
	{
		this->OpenDoor(deltaTime);
		this->lastOpenTime = world->GetTimeSeconds();
	}
	else if (world && ownerActor && this->pressurePlate && this->playerActor
		&&	(world->GetTimeSeconds() - this->lastOpenTime) > this->delayTime)
	{
		this->CloseDoor(deltaTime);
	}
}


void UJeJoOpenDoor::OpenDoor(const float deltaTime) noexcept
{
	if (AActor *const ownerActor = GetOwner())
	{
		// rotate from the current door position to target door opening angle
		FRotator rotateDoor{ ownerActor->GetActorRotation() };
		rotateDoor.Yaw = this->currentYaw = FMath::FInterpTo(
				this->currentYaw, this->targetAngle, deltaTime, this->openingSpeed
		);
		ownerActor->SetActorRotation(MoveTemp(rotateDoor));

		// play the audio once
		this->isCloseDoorSoundPlaying = false;
		if (this->audioComponet && !this->isOpenDoorSoundPlaying)
		{
			this->audioComponet->Play();
			this->isOpenDoorSoundPlaying = true;
		}
	}
}


void UJeJoOpenDoor::CloseDoor(const float deltaTime) noexcept
{
	if (AActor *const ownerActor = GetOwner())
	{
		// rotate from the current door position to the initial position
		FRotator rotateDoor{ ownerActor->GetActorRotation() };
		rotateDoor.Yaw = this->currentYaw = FMath::FInterpTo(
				this->currentYaw, this->initialYaw, deltaTime, this->closingSpeed
		);
		ownerActor->SetActorRotation(MoveTemp(rotateDoor));

		// play the audio once
		this->isOpenDoorSoundPlaying = false;
		if (this->audioComponet && !this->isCloseDoorSoundPlaying)
		{
			this->audioComponet->Play();
			this->isCloseDoorSoundPlaying = true;
		}
	}
}


void UJeJoOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	AActor* const ownerActor = GetOwner();

	// set the initial values
	this->initialYaw = this->currentYaw = ownerActor->GetActorRotation().Yaw;
	this->targetAngle += this->initialYaw;

	// log messages
	UE_LOG(LogJeJoOpenDoor, Log, TEXT("BeginPlay() - this->initialYaw: %f"), this->initialYaw);
	UE_LOG(LogJeJoOpenDoor, Log, TEXT("BeginPlay() - this->currentYaw: %f"), this->currentYaw);
	UE_LOG(LogJeJoOpenDoor, Log, TEXT("BeginPlay() - this->targetAngle: %f"), this->targetAngle);

	// check whether pressure plate has been added
	if (!this->pressurePlate)
	{
		UE_LOG(LogJeJoOpenDoor, Error
			, TEXT("BeginPlay() - No pressure-plate set for: %s!"), *(ownerActor->GetName()));
	}

	// set the actor that opens (i.e. Door)
	this->playerActor = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!this->playerActor)
	{
		UE_LOG(LogJeJoOpenDoor, Error, TEXT("BeginPlay() - No player pawn found!"));
	}

	// set the audio component
	this->SetAudioComponet();
}


float UJeJoOpenDoor::GetTotalOverlappingActorsMass() const noexcept
{
	if (!this->pressurePlate)
	{
		UE_LOG(LogJeJoOpenDoor, Error
			, TEXT("GetTotalOverlappingActorsMass() - No pressure plate found pawn found!"));
		return 0.f;
	}

	TSet<AActor*> overlappingActors;
	this->pressurePlate->GetOverlappingActors(overlappingActors);

	float toatlMass{ 0.f };
	for (const AActor* const actor : overlappingActors)
	{
		if (!actor)
		{
			continue;
		}

		if (const auto* const comp = actor->FindComponentByClass<UPrimitiveComponent>())
		{
			toatlMass += comp->GetMass();
			UE_LOG(LogJeJoOpenDoor, Error
				, TEXT("GetTotalOverlappingActorsMass() - Actor: %s"), *(actor->GetName()));
		}
	}
	UE_LOG(LogJeJoOpenDoor, Warning,
		TEXT("GetTotalOverlappingActorsMass() - Total mass: %f"), toatlMass);
	return toatlMass;
}


void UJeJoOpenDoor::SetAudioComponet() noexcept
{
	if (const AActor* const ownerActor = GetOwner())
	{
		if (this->audioComponet = ownerActor->FindComponentByClass<UAudioComponent>();
			!this->audioComponet)
		{
			UE_LOG(LogJeJoOpenDoor, Error
				, TEXT("SetAudioComponet() - No audio-component set for: %s!"), *(ownerActor->GetName()));
		}
	}
	else
	{
		UE_LOG(LogJeJoOpenDoor, Error
			, TEXT("SetAudioComponet() - No parent actor found for the component!"));
	}
}

