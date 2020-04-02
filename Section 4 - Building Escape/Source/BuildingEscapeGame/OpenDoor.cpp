// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	const FRotator CurrentRotation{ GetOwner()->GetActorRotation() };
	const FRotator RotateTo{ CurrentRotation.Pitch, CurrentRotation.Yaw - 90.0f, CurrentRotation.Roll };
	GetOwner()->SetActorRotation(RotateTo);
}

void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
