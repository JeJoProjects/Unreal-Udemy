/****************************************************************************************
 * Grabber component implementation.
 *
 * @Authur : JeJo
 * @license: MIT
****************************************************************************************/

#include "DrawDebugHelpers.h"
#include "CollisionQueryParams.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "JeJoGrabber.h"

DEFINE_LOG_CATEGORY(LogJeJoGrabber)


UJeJoGrabber::UJeJoGrabber()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UJeJoGrabber::TickComponent(
	float deltaTime, ELevelTick tickType, FActorComponentTickFunction* thisTickFunction)
{
	Super::TickComponent(deltaTime, tickType, thisTickFunction);

	const UWorld* const world = GetWorld();
	if (const auto* const playerController = world->GetFirstPlayerController())
	{
		// get the start and end point of player's view point
		auto [playerViewPointStart, playerViewPointEnd] = this->GetViewPointStartEnd();
		DrawDebugLine(world, playerViewPointStart, playerViewPointEnd,
			FColor::Green,false, 0.f, 0u, 5.f);

		// ray-cast
		this->RayCastTracing(MoveTemp(playerViewPointStart), MoveTemp(playerViewPointEnd));
	}
	// log message
}


void UJeJoGrabber::Grab() noexcept
{
	UE_LOG(LogJeJoGrabber, Error
		, TEXT("Grabber pressed!... The owner name: %s"), *(GetOwner()->GetName()));
}


void UJeJoGrabber::Release() noexcept
{
	UE_LOG(LogJeJoGrabber, Error, TEXT("Grabber Released!"));
}


void UJeJoGrabber::BeginPlay()
{
	Super::BeginPlay();
	this->FindPhysicsHandle();	
	this->BindActions();
}

void UJeJoGrabber::FindPhysicsHandle() noexcept
{
	if (const AActor* const ownerActor = GetOwner())
	{
		// check whether physics handler has attached to the owner actor!
		this->physicsHandle = ownerActor->FindComponentByClass<UPhysicsHandleComponent>();

		if (this->physicsHandle)
		{

		}
		else
		{
			UE_LOG(LogJeJoGrabber, Error
				, TEXT("No Physics handle component has not been found on actor: %s")
				, *(ownerActor->GetName()));
		}
	}
	else
	{
		UE_LOG(LogJeJoGrabber, Error
			, TEXT("UJeJoGrabber::FindPhysicsHandle(): No parent actor found for the component!"));
	}
}


void UJeJoGrabber::BindActions() noexcept
{
	if (const AActor* const ownerActor = GetOwner())
	{
		// check for the input-component and bind actions to it!
		this->inputComponet = ownerActor->FindComponentByClass<UInputComponent>();
		if (this->inputComponet)
		{
			this->inputComponet->BindAction(FName{ "Select" }, EInputEvent::IE_Pressed
				, this, &UJeJoGrabber::Grab);
			this->inputComponet->BindAction(FName{ "Select" }, EInputEvent::IE_Released
				, this, &UJeJoGrabber::Release);
		}
		else
		{
			UE_LOG(LogJeJoGrabber, Error
				, TEXT("UJeJoGrabber::BindActions(): No input component has not been found on actor: %s")
				, *(ownerActor->GetName()));
		}
	}
	else
	{
		UE_LOG(LogJeJoGrabber, Error
			, TEXT("UJeJoGrabber::BindActions(): No parent actor found for the component!"));
	}
}


void UJeJoGrabber::RayCastTracing(FVector&& startPoint, FVector&& endPoint) const noexcept
{
	const AActor* const ownerActor = GetOwner();
	if (!ownerActor)
	{
		return; // nothing to do!
	}

	FHitResult hitResult{ EForceInit::ForceInit };
	FCollisionObjectQueryParams collisionChannel{ ECollisionChannel::ECC_PhysicsBody };
	FCollisionQueryParams traceParams{ FName{}, false, ownerActor };

	if (GetWorld()->LineTraceSingleByObjectType(hitResult, startPoint, endPoint
		, collisionChannel, traceParams))
	{
		if (hitResult.bBlockingHit && hitResult.GetActor())
		{
			// UE_LOG(LogJeJoGrabber, Error
			// , TEXT("Line trace has hit: %s"), *(hitResult.GetActor()->GetName()));
		}
	}
}


std::pair<FVector, FVector> UJeJoGrabber::GetViewPointStartEnd() const noexcept
{
	if (const auto* const playerController	= GetWorld()->GetFirstPlayerController())
	{
		FVector playerViewPointLocation{ EForceInit::ForceInit };
		FRotator playeViewPointrRotation{ EForceInit::ForceInit };
		playerController->GetPlayerViewPoint(playerViewPointLocation, playeViewPointrRotation);

		return std::pair<FVector, FVector>{ playerViewPointLocation
			, playerViewPointLocation + playeViewPointrRotation.Vector() * this->range
		};
	}

	UE_LOG(LogJeJoGrabber, Error
		, TEXT("Could not find the start and end view point of the player"));
	return {};
}

