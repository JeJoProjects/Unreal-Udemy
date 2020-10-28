/****************************************************************************************
 * Grabber component implementation.
 *
 * @Authur : JJ
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

	// check whether the physics handle is attached
	if (this->physicsHandle->GrabbedComponent)
	{
		auto [traceStart, traceEnd] = this->GetViewPointStartAndEnd();
		this->physicsHandle->SetTargetLocation(MoveTemp(traceEnd));
	}
}


void UJeJoGrabber::Grab() noexcept
{
	UE_LOG(LogJeJoGrabber, Warning
		, TEXT("Grab() - Grabber pressed!\nThe owner name: %s"), *(GetOwner()->GetName()));

		
	// if we hit something then attach the physics handle.
	FHitResult hitResult{ this->GetFirstPhysicsBodyInReach() };

	if (hitResult.bBlockingHit && hitResult.GetActor())
	{
		auto [traceStart, traceEnd] = this->GetViewPointStartAndEnd();
		UPrimitiveComponent* const componentToGrab{ hitResult.GetComponent() };
		
		check(componentToGrab);
		this->physicsHandle->GrabComponentAtLocation(
			componentToGrab, EName::NAME_None, MoveTemp(traceEnd));
	}

}


void UJeJoGrabber::Release() noexcept
{
	if (this->physicsHandle->GrabbedComponent)
	{
		this->physicsHandle->ReleaseComponent();
	}
	UE_LOG(LogJeJoGrabber, Warning, TEXT("Release() - Grabber Released!"));
}


void UJeJoGrabber::BeginPlay()
{
	Super::BeginPlay();
	this->SetPhysicsHandle();	
	this->BindActions();
}


FHitResult UJeJoGrabber::GetFirstPhysicsBodyInReach() const noexcept
{
	const UWorld* const world = GetWorld();
	if (!world)
	{
		UE_LOG(LogJeJoGrabber, Error
			, TEXT(":GetFirstPhysicsBodyInReach(): World not found!"));
		return {}; // return the default constructed HitResult!
	}

	const auto* const playerController = world->GetFirstPlayerController();
	if (!playerController)
	{
		UE_LOG(LogJeJoGrabber, Error
			, TEXT(":GetFirstPhysicsBodyInReach(): PlayerController not found!"));
		return {}; // return the default constructed HitResult!
	}

	const AActor* const ownerActor = GetOwner();
	if (!ownerActor)
	{
		UE_LOG(LogJeJoGrabber, Error
			, TEXT(":GetFirstPhysicsBodyInReach(): Owner actor not found!"));
		return {}; // return the default constructed HitResult!
	}

	// get the start and end point of player's view point
	const auto [playerViewPointStart, playerViewPointEnd] = this->GetViewPointStartAndEnd();
	DrawDebugLine(world, playerViewPointStart, playerViewPointEnd,
		FColor::Green, false, 0.f, 0u, 5.f);

	// ray-cast
	FHitResult hitResult{ EForceInit::ForceInit };
	FCollisionObjectQueryParams collisionChannel{ ECollisionChannel::ECC_PhysicsBody };
	FCollisionQueryParams traceParams{ FName{}, false, ownerActor };

	if (world->LineTraceSingleByObjectType(
		hitResult, playerViewPointStart, playerViewPointEnd, collisionChannel, traceParams)
		&& hitResult.bBlockingHit && hitResult.GetActor())
	{
		UE_LOG(LogJeJoGrabber, Error
			, TEXT(":GetFirstPhysicsBodyInReach(): Line trace has hit: %s")
			, *(hitResult.GetActor()->GetName()));
	}
	return MoveTemp(hitResult); // return the HitResult!
}


void UJeJoGrabber::SetPhysicsHandle() noexcept
{
	if (const AActor* const ownerActor = GetOwner())
	{
		// check whether physics handler has attached to the owner actor!
		if (this->physicsHandle = ownerActor->FindComponentByClass<UPhysicsHandleComponent>();
			!this->physicsHandle)
		{
			UE_LOG(LogJeJoGrabber, Error
				, TEXT("SetPhysicsHandle() - No Physics handle component has not been found on actor: %s")
				, *(ownerActor->GetName()));
		}
	}
	else
	{
		UE_LOG(LogJeJoGrabber, Error
			, TEXT("SetPhysicsHandle() - No parent actor found for the component!"));
	}
}


void UJeJoGrabber::BindActions() noexcept
{
	if (const AActor* const ownerActor = GetOwner())
	{
		// check for the input-component and bind actions to it!
		this->inputComponet = ownerActor->FindComponentByClass<UInputComponent>();
		check(this->inputComponet);
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
				, TEXT("BindActions() - No input component has not been found on actor: %s")
				, *(ownerActor->GetName()));
		}
	}
	else
	{
		UE_LOG(LogJeJoGrabber, Error
			, TEXT("BindActions() - No parent actor found for the component!"));
	}
}


SPair<FVector, FVector> UJeJoGrabber::GetViewPointStartAndEnd() const noexcept
{
	if (const auto* const playerController	= GetWorld()->GetFirstPlayerController())
	{
		FVector playerViewPointLocation{ EForceInit::ForceInit };
		FRotator playeViewPointrRotation{ EForceInit::ForceInit };
		playerController->GetPlayerViewPoint(playerViewPointLocation, playeViewPointrRotation);

		return SPair<FVector, FVector>{ playerViewPointLocation
			, MoveTemp(playerViewPointLocation)
			+ playeViewPointrRotation.Vector() * this->rayCastingRange
		};
	}

	UE_LOG(LogJeJoGrabber, Error
		, TEXT("GetViewPointStartAndEnd() - Could not find the start and end view point of the player"));
	return {}; // return an default initialized pair!
}

