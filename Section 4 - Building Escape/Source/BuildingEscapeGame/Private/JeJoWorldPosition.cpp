// Fill out your copyright notice in the Description page of Project Settings.

#include "JeJoWorldPosition.h"
#include "GameFramework/Actor.h"

// Called when the game starts
void UJeJoWorldPosition::BeginPlay()
{
	Super::BeginPlay();

	const FString ObjectName{ GetOwner()->GetName() };
	const FString ObjectLocation{ GetOwner()->GetActorLocation().ToString() };

	// UE_LOG(LogTemp, Warning, TEXT("The %s position in the world is: %s"), *ObjectName, *ObjectLocation);
}

// Called every frame
void UJeJoWorldPosition::TickComponent(float deltaTime, ELevelTick tickType, FActorComponentTickFunction* thisTickFunction)
{
	Super::TickComponent(deltaTime, tickType, thisTickFunction);
}

// Sets default values for this component's properties
UJeJoWorldPosition::UJeJoWorldPosition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}
