/****************************************************************************************
 * Grabber component
 *
 * @Authur : JJ
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
	UPROPERTY(EditAnywhere, Category = "JJGrabber")
	float rayCastingRange{ 100.f };

	UPROPERTY(VisibleAnywhere, Category = "JJGrabber")
	UInputComponent* inputComponet{ nullptr };

	UPROPERTY(VisibleAnywhere, Category = "JJGrabber")
	UPhysicsHandleComponent* physicsHandle { nullptr };

	// Sets default values for this component's properties
	UJeJoGrabber();

	// Called every frame
	void TickComponent(float, ELevelTick, FActorComponentTickFunction*) override;

	UFUNCTION(BlueprintCallable, Category = "JJGrabber")
	void Grab() noexcept;

	UFUNCTION(BlueprintCallable, Category = "JJGrabber")
	void Release() noexcept;

protected:
	// Called when the game starts
	void BeginPlay() override;

private:
	UFUNCTION(BlueprintCallable, Category = "JJGrabber")
	FHitResult GetFirstPhysicsBodyInReach() const noexcept;

	UFUNCTION(BlueprintCallable, Category = "JJGrabber")
	void SetPhysicsHandle() noexcept;

	UFUNCTION(BlueprintCallable, Category = "JJGrabber")
	void BindActions() noexcept;

	SPair<FVector, FVector> GetViewPointStartAndEnd() const noexcept;
};

