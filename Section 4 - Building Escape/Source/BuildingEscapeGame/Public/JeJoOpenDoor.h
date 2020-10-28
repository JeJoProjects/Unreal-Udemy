/****************************************************************************************
 * Open door component.
 *
 * @Authur : JJ
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
class UAudioComponent;


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BUILDINGESCAPEGAME_API UJeJoOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "JJOpenDoor")
	float targetAngle{ 90.f };

	UPROPERTY(EditAnywhere, Category = "JJOpenDoor")
	float openingSpeed{ 2.f };

	UPROPERTY(EditAnywhere, Category = "JJOpenDoor")
	float closingSpeed{ 0.8f };

	UPROPERTY(EditAnywhere, Category = "JJOpenDoor")
   float delayTime{ 1.f };

	UPROPERTY(EditAnywhere, Category = "JJOpenDoor")
   float massToOpenDoor{ 50.f };

	UPROPERTY(EditAnywhere, Category = "JJOpenDoor")
	ATriggerVolume* pressurePlate{ nullptr };

	UPROPERTY(EditAnywhere, Category = "JJOpenDoor")
	AActor* playerActor{ nullptr };

	UPROPERTY(VisibleAnywhere, Category = "JJGrabber")
	UAudioComponent* audioComponet { nullptr };

	// Sets default values for this component's properties
	UJeJoOpenDoor();

	// Called every frame
	void TickComponent(float, ELevelTick, FActorComponentTickFunction*) override;

	UFUNCTION(BlueprintCallable, Category = "JJOpenDoor")
	void OpenDoor(const float deltaTime) noexcept;

	UFUNCTION(BlueprintCallable, Category = "JJOpenDoor")
	void CloseDoor(const float deltaTime) noexcept;

protected:
	// Called when the game starts
	void BeginPlay() override;

private:
	float initialYaw;
	float currentYaw;
	float lastOpenTime;

	// tracks whether the sound has been played.
	bool isOpenDoorSoundPlaying;
	bool isCloseDoorSoundPlaying;

	UFUNCTION(BlueprintCallable, Category = "JJGrabber")
	float GetTotalOverlappingActorsMass() const noexcept;

	UFUNCTION(BlueprintCallable, Category = "JJGrabber")
	void SetAudioComponet() noexcept;
};
