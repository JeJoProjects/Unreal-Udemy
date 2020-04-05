// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "GameFramework/Actor.h"

void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	TargetYaw += InitialYaw;
}

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// debug log message
	UE_LOG(LogTemp, Warning, TEXT("%s"), *(GetOwner()->GetActorRotation().ToString()));
	UE_LOG(LogTemp, Warning, TEXT("Yaw: %f"), GetOwner()->GetActorRotation().Yaw);

	// rotate from the current door position
	CurrentYaw = FMath::Lerp(CurrentYaw, TargetYaw,0.02f);
	FRotator RotateDoor{GetOwner()->GetActorRotation()};
	RotateDoor.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(RotateDoor);
}
