// Fill out your copyright notice in the Description page of Project Settings.

#include "DrawDebugHelpers.h"
#include "CollisionQueryParams.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "JeJoGrabber.h"

DEFINE_LOG_CATEGORY(LogJeJoGrabber)

std::pair<FVector, FVector> UJeJoGrabber::GetViewPointStartEnd() const noexcept
{
	if (const APlayerController* const playerController = GetWorld()->GetFirstPlayerController())
	{
		FVector playerViewPointLocation{ EForceInit::ForceInit };
		FRotator playeViewPointrRotation{ EForceInit::ForceInit };
		playerController->GetPlayerViewPoint(playerViewPointLocation, playeViewPointrRotation);

		return std::pair<FVector, FVector>{ playerViewPointLocation
			, playerViewPointLocation + playeViewPointrRotation.Vector() * this->range
		};
	}

	UE_LOG(LogJeJoGrabber, Error, TEXT("Could not find the start and end view point of the player"));
	return {};
}


void UJeJoGrabber::RayCastTracing(
	FVector&& startPoint, FVector&& endPoint) const noexcept
{
	const AActor *const ownerActor = GetOwner();
	if (!ownerActor)
	{
		return; // nothing to do!
	}
	
	FHitResult hitResult{ EForceInit::ForceInit };
	FCollisionObjectQueryParams collisionChannel{ ECollisionChannel::ECC_PhysicsBody };
	FCollisionQueryParams traceParams{ FName{}, false, ownerActor };

	if (GetWorld()->LineTraceSingleByObjectType(hitResult, startPoint, endPoint, collisionChannel, traceParams))
	{
		if (hitResult.bBlockingHit && hitResult.GetActor())
		{
			// UE_LOG(LogJeJoGrabber, Error, TEXT("Line trace has hit: %s"), *(hitResult.GetActor()->GetName()));
		}
	}
}


void UJeJoGrabber::BeginPlay()
{
	Super::BeginPlay();

	// check whether physics handler has attached to the owner actor!
	if (const AActor* const ownerActor = GetOwner())
	{
		this->physicsHandle = ownerActor->FindComponentByClass<UPhysicsHandleComponent>();

		if (this->physicsHandle)
		{
			UE_LOG(LogJeJoGrabber, Log, TEXT("Physics handle component has been found on actor: %s"), *(ownerActor->GetName()));
		}
		else
		{
			UE_LOG(LogJeJoGrabber, Error, TEXT("No Physics handle component has not been found on actor: %s"), *(ownerActor->GetName()));
		}
	}
}


UJeJoGrabber::UJeJoGrabber()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UJeJoGrabber::TickComponent(
	float deltaTime, ELevelTick tickType, FActorComponentTickFunction* thisTickFunction)
{
	Super::TickComponent(deltaTime, tickType, thisTickFunction);

	const UWorld* const world = GetWorld();
	if (const APlayerController* const playerController = world->GetFirstPlayerController())
	{
		// get the start and end point of player's view point
		auto [playerViewPointStart, playerViewPointEnd] = this->GetViewPointStartEnd();
		DrawDebugLine(world, playerViewPointStart, playerViewPointEnd, FColor::Green, false, 0.f, 0u, 5.f);

		// ray-cast
		this->RayCastTracing(MoveTemp(playerViewPointStart), MoveTemp(playerViewPointEnd));
	}
	// log message
}

