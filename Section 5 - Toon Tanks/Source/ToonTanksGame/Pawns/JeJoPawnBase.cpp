/****************************************************************************************
 * -------------------- implementation.
 *
 * @Authur : JeJo
 * @license: MIT
****************************************************************************************/
#include "JeJoPawnBase.h"
#include "Components/InputComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"

DEFINE_LOG_CATEGORY(LogJeJoPawnBase)

// Sets default values
AJeJoPawnBase::AJeJoPawnBase() noexcept
	: APawn{}
	, capsuleComp{ CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider")) }
	, baseStaticMeshComp{ CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Static Mesh")) }
	, turrentStaticMeshComp{ CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turrent Static Mesh")) }
	, projectileSpawnPointComp{ CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point")) }
{
	PrimaryActorTick.bCanEverTick = true;

	// set the Capsule Component to be the Root Component
	RootComponent = this->capsuleComp;
	// attach the rest of the components, one after the another!
	this->baseStaticMeshComp->SetupAttachment(RootComponent);
	this->turrentStaticMeshComp->SetupAttachment(this->baseStaticMeshComp);
	this->projectileSpawnPointComp->SetupAttachment(this->turrentStaticMeshComp);
}


void AJeJoPawnBase::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
}


void AJeJoPawnBase::SetupPlayerInputComponent(UInputComponent* playerInputComp)
{
	Super::SetupPlayerInputComponent(playerInputComp);
}


void AJeJoPawnBase::RotateTurrent_Implementation(const FVector& targetMesh) noexcept
{
	const FVector startLocation{ this->turrentStaticMeshComp->GetComponentLocation() };
	const FVector lookAtTargetLocation{ targetMesh.X, targetMesh.Y, startLocation.Z };
	FRotator turrentRotation{ (lookAtTargetLocation - startLocation).Rotation() };
	this->turrentStaticMeshComp->SetWorldRotation(MoveTemp(turrentRotation));
}


void AJeJoPawnBase::Fire_Implementation() const
{
	UE_LOG(LogJeJoPawnBase, Warning
		, TEXT("Super::Fire_Implementation() - Player-Pawn is in the range!"));
}


void AJeJoPawnBase::HandleDestruction_Implementation() noexcept
{

}


void AJeJoPawnBase::BeginPlay()
{
	Super::BeginPlay();

	// check all set!
	this->CheckComponets();
}


void AJeJoPawnBase::CheckComponets() const noexcept
{
	if (!GetWorld())
	{
		UE_LOG(LogJeJoPawnBase, Error, TEXT("BeginPlay() - World has not been set!"));
	}

	if (!RootComponent)
	{
		UE_LOG(LogJeJoPawnBase, Error
			, TEXT("Root component (aka Capsule Component) has not been set."));
	}
	if (!this->baseStaticMeshComp)
	{
		UE_LOG(LogJeJoPawnBase, Error, TEXT("Base SM component has not been set."));
	}
	if (!this->turrentStaticMeshComp)
	{
		UE_LOG(LogJeJoPawnBase, Error, TEXT("Turrent SM component has not been set."));
	}
	if (!this->projectileSpawnPointComp)
	{
		UE_LOG(LogJeJoPawnBase, Error
			, TEXT("Projectile spawn point component has not been set."));
	}
}

