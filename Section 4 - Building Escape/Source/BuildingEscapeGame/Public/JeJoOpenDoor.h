// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "JeJoOpenDoor.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BUILDINGESCAPEGAME_API UJeJoOpenDoor : public UActorComponent
{
	GENERATED_BODY()

private:
	float InitialYaw{ 0.0f };
	float CurrentYaw;

	float DoorLastOpen{ 0.0f };

	UPROPERTY(EditAnywhere, Category = "UOpenDoor")
	float DoorOpenAngle{ 90.f };

	UPROPERTY(EditAnywhere, Category = "UOpenDoor")
	float DoorOpenSpeed{ 2.0f };

	UPROPERTY(EditAnywhere, Category = "UOpenDoor")
	float DoorCloseSpeed{ 0.8f };

	UPROPERTY(EditAnywhere, Category = "UOpenDoor")
	float DoorCloseDelay{ 20.f };

	UPROPERTY(EditAnywhere, Category = "UOpenDoor")
	ATriggerVolume* PressurePlate;

	UPROPERTY(EditAnywhere, Category = "UOpenDoor")
	AActor* ActorThatOpen;

protected:
	// Called when the game starts
	void BeginPlay() override;

public:
	// Sets default values for this component's properties
	UJeJoOpenDoor();
	// Called every frame
	void TickComponent(float, ELevelTick, FActorComponentTickFunction*) override;

	void OpenDoor(const float) noexcept;
	void CloseDoor(const float) noexcept;
};
