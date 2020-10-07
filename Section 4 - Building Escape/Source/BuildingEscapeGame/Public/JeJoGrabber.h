// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "JeJoGrabber.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BUILDINGESCAPEGAME_API UJeJoGrabber : public UActorComponent
{
	GENERATED_BODY()

private:

protected:
	// Called when the game starts
	void BeginPlay() override;

public:
	// Sets default values for this component's properties
	UJeJoGrabber();

	// Called every frame
	void TickComponent(float, ELevelTick, FActorComponentTickFunction*) override;
};
