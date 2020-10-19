// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include <utility>

#include "JeJoGrabber.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogJeJoGrabber, Log, All);

// forward declaration
class UPhysicsHandleComponent;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BUILDINGESCAPEGAME_API UJeJoGrabber : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "UJeJoGrabber")
	float range{ 100.f };

	UPROPERTY(VisibleAnywhere, Category = "UJeJoGrabber")
	UPhysicsHandleComponent* physicsHandle{ nullptr };

	std::pair<FVector, FVector> GetViewPointStartEnd() const noexcept;

	void RayCastTracing(FVector&& startPoint, FVector&& endPoint) const noexcept;

protected:
	// Called when the game starts
	void BeginPlay() override;

public:
	// Sets default values for this component's properties
	UJeJoGrabber();

	// Called every frame
	void TickComponent(float, ELevelTick, FActorComponentTickFunction*) override;
};
