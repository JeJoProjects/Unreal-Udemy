// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "JeJoOpenDoor.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogJeJoOpenDoor, Log, All);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BUILDINGESCAPEGAME_API UJeJoOpenDoor : public UActorComponent
{
	GENERATED_BODY()

private:
	float InitialYaw{ 0.0f };
	float CurrentYaw;

	float DoorLastOpen{ 0.0f };

	UPROPERTY(EditAnywhere, Category = "UJeJoOpenDoor")
	float DoorOpenAngle{ 90.f };

	UPROPERTY(EditAnywhere, Category = "UJeJoOpenDoor")
	float DoorOpenSpeed{ 2.0f };

	UPROPERTY(EditAnywhere, Category = "UJeJoOpenDoor")
	float DoorCloseSpeed{ 0.8f };

	UPROPERTY(EditAnywhere, Category = "UJeJoOpenDoor")
	float DoorCloseDelay{ 20.f };

	UPROPERTY(EditAnywhere, Category = "UJeJoOpenDoor")
	ATriggerVolume* PressurePlate;

	UPROPERTY(EditAnywhere, Category = "UJeJoOpenDoor")
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
