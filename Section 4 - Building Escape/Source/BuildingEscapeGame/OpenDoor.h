// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BUILDINGESCAPEGAME_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

private:
	float InitialYaw{0.0f};
	float CurrentYaw;

	float DoorLastOpen{0.0f};
	const float DoorCloseDelay{20.f};

	UPROPERTY(EditAnywhere)
	float TargetYaw{90.f};

	UPROPERTY(EditAnywhere)
	ATriggerVolume *PressurePlate;

	UPROPERTY(EditAnywhere)
	AActor *ActorThatOpen;

protected:
	// Called when the game starts
	void BeginPlay() override;

public:
	// Sets default values for this component's properties
	UOpenDoor();

	// Called every frame
	void TickComponent(float, ELevelTick, FActorComponentTickFunction *) override;

	void OpenDoor(const float) noexcept;
	void CloseDoor(const float) noexcept;
};
