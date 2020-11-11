/****************************************************************************************
 * -------------------- implementation.
 *
 * @Authur : JeJo
 * @license: MIT
****************************************************************************************/
#include "JeJoProjectileBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Components/StaticMeshComponent.h"

DEFINE_LOG_CATEGORY(LogJeJoProjectileBase)


AJeJoProjectileBase::AJeJoProjectileBase() noexcept
	: AActor{}
	, projectileStaticMeshComp{ CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Static Mesh Component")) }
	, projectileMovementComp{ CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component")) }
{
	PrimaryActorTick.bCanEverTick = false;
	Super::InitialLifeSpan = 3.f;
	this->SetupComponets();
}


void AJeJoProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AJeJoProjectileBase::SetupComponets() noexcept
{
	if (RootComponent = this->projectileStaticMeshComp; !RootComponent)
	{
		UE_LOG(LogJeJoProjectileBase, Error
			, TEXT("Root component (aka Static Mesh Component) has not been set."));
	}
	if (this->projectileMovementComp)
	{
		this->projectileMovementComp->InitialSpeed = this->movementSpeed;
		this->projectileMovementComp->MaxSpeed = this->movementSpeed;
	}
	else
	{
		UE_LOG(LogJeJoProjectileBase, Error
			, TEXT("Projectile movement component has not been set for: %s"), *GetClass()->GetName());
	}
}


void AJeJoProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

