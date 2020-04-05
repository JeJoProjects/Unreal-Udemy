// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BUILDINGESCAPEGAME_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()
private:
	float TargetYaw{ 90.0f };

protected:
	// Called when the game starts
	void BeginPlay() override;

public:
	// Sets default values for this component's properties
	UOpenDoor();

	// Called every frame
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
};
