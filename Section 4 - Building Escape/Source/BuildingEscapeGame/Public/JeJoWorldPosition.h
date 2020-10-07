// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "JeJoWorldPosition.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogJeJoWorldPosition, Log, All);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BUILDINGESCAPEGAME_API UJeJoWorldPosition : public UActorComponent
{
	GENERATED_BODY()

private:

protected:
	// Called when the game starts
	void BeginPlay() override;

	// Called every frame
	void TickComponent(float, ELevelTick, FActorComponentTickFunction*) override;

public:	
	// Sets default values for this component's properties
	UJeJoWorldPosition();
};
