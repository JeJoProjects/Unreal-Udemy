/****************************************************************************************
 * -------------------- implementation.
 *
 * @Authur : JeJo
 * @license: MIT
****************************************************************************************/
#include "JeJoPawnBase.h"
#include "Components/InputComponent.h"

// Sets default values
AJeJoPawnBase::AJeJoPawnBase()
	: APawn{}
{
	PrimaryActorTick.bCanEverTick = true;
}


void AJeJoPawnBase::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
}


void AJeJoPawnBase::SetupPlayerInputComponent(UInputComponent* playerInputComponent)
{
	Super::SetupPlayerInputComponent(playerInputComponent);
}


void AJeJoPawnBase::BeginPlay()
{
	Super::BeginPlay();	
}

