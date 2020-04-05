// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "GameFramework/Actor.h"

void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
}

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UE_LOG(LogTemp, Warning, TEXT("Current time: %f"), DeltaTime);

	const FRotator CurrentRotation{GetOwner()->GetActorRotation()};
	const float CurrentYaw{CurrentRotation.Yaw};

	FRotator RotateTo{CurrentRotation.Pitch, TargetYaw, CurrentRotation.Roll};
	RotateTo.Yaw = FMath::FInterpTo(CurrentYaw, TargetYaw, DeltaTime, 2);

	GetOwner()->SetActorRotation(RotateTo);
}
