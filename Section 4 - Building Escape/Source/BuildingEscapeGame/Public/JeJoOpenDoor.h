/****************************************************************************************
 * Open door component.
 *
 * @Authur : JeJo
 * @license: MIT
****************************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "JeJoOpenDoor.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogJeJoOpenDoor, Log, All);

// forward declaration
class AActor;
class ATriggerVolume;


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BUILDINGESCAPEGAME_API UJeJoOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UJeJoOpenDoor();

	// Called every frame
	void TickComponent(float, ELevelTick, FActorComponentTickFunction*) override;

	UFUNCTION(BlueprintCallable, Category = "UJeJoOpenDoor")
	void OpenDoor(const float deltaTime) noexcept;

	UFUNCTION(BlueprintCallable, Category = "UJeJoOpenDoor")
	void CloseDoor(const float deltaTime) noexcept;

protected:
	// Called when the game starts
	void BeginPlay() override;

private:
	float initialYaw;
	float currentYaw;
	float lastOpenTime;

	UPROPERTY(EditAnywhere, Category = "UJeJoOpenDoor")
	float targetAngle{ 90.f };

	UPROPERTY(EditAnywhere, Category = "UJeJoOpenDoor")
	float openingSpeed{ 2.f };

	UPROPERTY(EditAnywhere, Category = "UJeJoOpenDoor")
	float closingSpeed{ 0.8f };

	UPROPERTY(EditAnywhere, Category = "UJeJoOpenDoor")
   float delayTime{ 1.f };

	UPROPERTY(EditAnywhere, Category = "UJeJoOpenDoor")
	ATriggerVolume* pressurePlate{ nullptr };

	UPROPERTY(EditAnywhere, Category = "UJeJoOpenDoor")
	AActor* playerActor{ nullptr };
};
