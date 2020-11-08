/****************************************************************************************
 * -------------------- implementation.
 *
 * @Authur : JeJo
 * @license: MIT
****************************************************************************************/
#include "JeJoPawnTurrent.h"
#include "JeJoPawnTank.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY(LogJeJoPawnTurrent)

AJeJoPawnTurrent::AJeJoPawnTurrent() noexcept
	: AJeJoPawnBase{}
	, fireRateTimerHandle {}
{
	PrimaryActorTick.bCanEverTick = true;
}


void AJeJoPawnTurrent::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	// if there is a valid player, which is in the range, then do fire.
	if (this->playerPawn && this->GetDistanceToPlayer() <= this->distanceRange)
	{
		// call the super with the current pawn-actor location
		Super::RotateTurrent_Implementation(this->playerPawn->GetActorLocation());
	}
}

float AJeJoPawnTurrent::GetDistanceToPlayer() const noexcept
{
	if (!this->playerPawn)
	{
		return 0.f; // done here!
	}
	return FVector::Dist(this->playerPawn->GetActorLocation(), GetActorLocation());
}


void AJeJoPawnTurrent::BeginPlay()
{
	Super::BeginPlay();

	// set the player pawn
	if (this->playerPawn = Cast<AJeJoPawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
		!this->playerPawn)
	{
		UE_LOG(LogJeJoPawnTurrent, Error, TEXT("BeginPlay() - The Player-Pawn has not been set!"));
	}

	// set the fire condition checker
	GetWorldTimerManager().SetTimer(this->fireRateTimerHandle, this
		, &ThisClass::CheckFireCondition, this->fireRate, true);
}


void AJeJoPawnTurrent::Fire_Implementation() noexcept
{
	Super::Fire_Implementation();
}


void AJeJoPawnTurrent::HandleDestruction_Implementation() noexcept
{
	// call base pawn class implementation to play effect
	Super::HandleDestruction_Implementation();
}


void AJeJoPawnTurrent::CheckFireCondition() noexcept
{
	UE_LOG(LogJeJoPawnTurrent, Log, TEXT("CheckFireCondition() - Fired condition checked!"));

	// if there is a valid player, which is in the range, then do fire.
	if (this->playerPawn && this->GetDistanceToPlayer() <= this->distanceRange)
	{
		this->Fire_Implementation();
	}
}

