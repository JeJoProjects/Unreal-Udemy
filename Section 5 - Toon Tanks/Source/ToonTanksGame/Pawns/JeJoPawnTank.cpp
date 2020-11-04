/****************************************************************************************
 * -------------------- implementation.
 *
 * @Authur : JeJo
 * @license: MIT
****************************************************************************************/
#include "JeJoPawnTank.h"
#include "Components/InputComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include <type_traits>

DEFINE_LOG_CATEGORY(LogJeJoPawnTank)

AJeJoPawnTank::AJeJoPawnTank() noexcept
   : AJeJoPawnBase{}
	, moveDirection{ 0.f }
	, rotationDirection{ EForceInit::ForceInit }
	, springArmComp{ CreateDefaultSubobject<USpringArmComponent>(TEXT("Sprint Arm Component")) }
	, cameraComp{ CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component")) }
{
   PrimaryActorTick.bCanEverTick = true;

	// set the components to the root.
	if (const auto rootComp = dynamic_cast<UCapsuleComponent*>(RootComponent))
	{
		this->springArmComp->SetupAttachment(RootComponent);
		this->cameraComp->SetupAttachment(this->springArmComp);
	}
	else
	{
		UE_LOG(LogJeJoPawnTank, Error, TEXT("AJeJoPawnTank() - No Root component found!"));
	}
}

void AJeJoPawnTank::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	this->Rotate();
	this->Move();
}


void AJeJoPawnTank::SetupPlayerInputComponent(UInputComponent* playerInputComp)
{
	Super::SetupPlayerInputComponent(playerInputComp);

	// setup the input bindings
	if (playerInputComp)
	{
		playerInputComp->BindAxis(FName{ "MoveForward" }, this, &AJeJoPawnTank::CalculateMoveInput);
		playerInputComp->BindAxis(FName{ "Turn" }, this, &AJeJoPawnTank::CalculateRotationInput);
	}
	else
	{
		UE_LOG(LogJeJoPawnTank, Error
			, TEXT("SetupPlayerInputComponent() - No Player Input Component found!"));
	}
}


void AJeJoPawnTank::BeginPlay()
{
	Super::BeginPlay();
}

void AJeJoPawnTank::CalculateMoveInput(const float value) noexcept
{
	this->moveDirection = FVector{
		value * this->moveSpeed * GetWorld()->DeltaTimeSeconds, 0.f, 0.f
	};
}

void AJeJoPawnTank::CalculateRotationInput(const float value) noexcept
{
	const float rotateAmount = value * this->rotateSpeed * GetWorld()->DeltaTimeSeconds;
	FRotator rotation{ 0.f, rotateAmount, 0.f };
	this->rotationDirection = FQuat{ MoveTemp(rotation) };
}

void AJeJoPawnTank::Move() noexcept
{
	AddActorLocalOffset(this->moveDirection, true);
}

void AJeJoPawnTank::Rotate() noexcept
{
	AddActorLocalRotation(this->rotationDirection, true);
}

