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
	UPROPERTY(VisibleAnywhere, Category = "UJeJoOpenDoor")
	float initialYaw;

	UPROPERTY(VisibleAnywhere, Category = "UJeJoOpenDoor")
	float currentYaw;

	UPROPERTY(VisibleAnywhere, Category = "UJeJoOpenDoor")
	float doorLastOpen;

	UPROPERTY(EditAnywhere, Category = "UJeJoOpenDoor")
	float doorOpenAngle;

	UPROPERTY(EditAnywhere, Category = "UJeJoOpenDoor")
	float doorOpenSpeed;

	UPROPERTY(EditAnywhere, Category = "UJeJoOpenDoor")
	float doorCloseSpeed;

	UPROPERTY(EditAnywhere, Category = "UJeJoOpenDoor")
	float doorCloseDelay;

	UPROPERTY(EditAnywhere, Category = "UJeJoOpenDoor")
	ATriggerVolume* pressurePlate;

	UPROPERTY(EditAnywhere, Category = "UJeJoOpenDoor")
	AActor* actorThatOpen;

protected:
	// Called when the game starts
	void BeginPlay() override;

public:
	// Sets default values for this component's properties
	UJeJoOpenDoor();
	// Called every frame
	void TickComponent(float, ELevelTick, FActorComponentTickFunction*) override;

	UFUNCTION(BlueprintCallable, Category = "UJeJoOpenDoor")
	void OpenDoor(const float deltaTime) noexcept;

	UFUNCTION(BlueprintCallable, Category = "UJeJoOpenDoor")
	void CloseDoor(const float deltaTime) noexcept;
};
