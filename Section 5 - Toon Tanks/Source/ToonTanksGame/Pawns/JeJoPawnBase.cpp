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


void AJeJoPawnBase::BeginPlay()
{
	Super::BeginPlay();	
}

