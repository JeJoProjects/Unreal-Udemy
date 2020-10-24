/****************************************************************************************
 * Grabber component
 *
 * @Authur : JeJo
 * @license: MIT
****************************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <utility>
#include "JeJoGrabber.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogJeJoGrabber, Log, All);

template<typename T1, typename T2>
struct BUILDINGESCAPEGAME_API SPair final : public std::pair<T1, T2>
{
	using std::pair<T1, T2>::pair;
};


// forward declaration
class UPhysicsHandleComponent;
class UInputComponent;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BUILDINGESCAPEGAME_API UJeJoGrabber : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UJeJoGrabber();

	// Called every frame
	void TickComponent(float, ELevelTick, FActorComponentTickFunction*) override;

	UFUNCTION(BlueprintCallable, Category = "UJeJoGrabber")
	void Grab() noexcept;


	UFUNCTION(BlueprintCallable, Category = "UJeJoGrabber")
	void Release() noexcept;

protected:
	// Called when the game starts
	void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "UJeJoGrabber")
	float rayCastingRange{ 100.f };

	UPROPERTY(VisibleAnywhere, Category = "UJeJoGrabber")
	UInputComponent* inputComponet{ nullptr };


	UPROPERTY(VisibleAnywhere, Category = "UJeJoGrabber")
	UPhysicsHandleComponent* physicsHandle { nullptr };

	FHitResult GetFirstPhysicsBodyInReach() const noexcept;
	void FindPhysicsHandle() noexcept;
	void BindActions() noexcept;
	SPair<FVector, FVector> GetViewPointStartAndEnd() const noexcept;
};
