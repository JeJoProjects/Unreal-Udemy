// Fill out your copyright notice in the Description page of Project Settings.

#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "JeJoGrabber.h"

DEFINE_LOG_CATEGORY(LogJeJoGrabber)

void UJeJoGrabber::BeginPlay()
{
	Super::BeginPlay();
}

UJeJoGrabber::UJeJoGrabber()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UJeJoGrabber::TickComponent(
	float deltaTime, ELevelTick tickType, FActorComponentTickFunction* thisTickFunction)
{
	Super::TickComponent(deltaTime, tickType, thisTickFunction);

	// get player's vie point informations
	const UWorld* const world = GetWorld();
	if (const APlayerController* const playerController = world->GetFirstPlayerController())
	{
		FVector playerViewPointLocation{ EForceInit::ForceInit };
		FRotator playeViewPointrRotation{ EForceInit::ForceInit };
		playerController->GetPlayerViewPoint(playerViewPointLocation, playeViewPointrRotation);

		DrawDebugLine(world, playerViewPointLocation
			, playerViewPointLocation + playeViewPointrRotation.Vector() * this->range
			, FColor::Blue, false, 0.f, 0u, 5.f);

		// UE_LOG(LogJeJoGrabber, Warning, TEXT("Player Location: %s | Rotation: %s")
		// 	, *playerViewPointLocation.ToString(), *playeViewPointrRotation.ToString());
	}

	// log message

}

