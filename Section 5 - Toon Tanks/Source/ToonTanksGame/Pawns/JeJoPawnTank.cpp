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
#include "GameFramework/PlayerController.h"

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

	if (this->playerController && this->playerController->IsValidLowLevel())
	{
		FHitResult traceHitResult{ EForceInit::ForceInit };
		this->playerController->GetHitResultUnderCursor(ECC_Visibility, false, traceHitResult);
		// call the super with the hit impact point
		Super::RotateTurrent_Implementation(static_cast<FVector>(traceHitResult.ImpactPoint));
	}
}


void AJeJoPawnTank::SetupPlayerInputComponent(UInputComponent* playerInputComp)
{
	Super::SetupPlayerInputComponent(playerInputComp);

	// setup the input bindings
	if (playerInputComp)
	{
		playerInputComp->BindAction(FName{ "Fire" }, IE_Pressed, this, &ThisClass::Fire);
		playerInputComp->BindAxis(FName{ "MoveForward" }, this, &ThisClass::CalculateMoveInput);
		playerInputComp->BindAxis(FName{ "Turn" }, this, &ThisClass::CalculateRotationInput);
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

	// set the player controller
	this->playerController = Cast<APlayerController>(GetController());

	// check all set!
	this->CheckComponets();
}


void AJeJoPawnTank::CheckComponets() const noexcept
{
	Super::CheckComponets();

	if (!this->springArmComp)
	{
		UE_LOG(LogJeJoPawnBase, Error, TEXT("Spring arm component has not been set."));
	}
	if (!this->cameraComp)
	{
		UE_LOG(LogJeJoPawnBase, Error, TEXT("Camera component has not been set."));
	}
	if (!this->playerController)
	{
		UE_LOG(LogJeJoPawnBase, Error, TEXT("Player controller has not been set."));
	}
}


void AJeJoPawnTank::Fire_Implementation() const
{

}


void AJeJoPawnTank::HandleDestruction_Implementation() noexcept
{
	// call base pawn class implementation to play effect
	Super::HandleDestruction_Implementation();
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

