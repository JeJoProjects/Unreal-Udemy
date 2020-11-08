// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JeJoPawnBase.h"
#include "JeJoPawnTurrent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogJeJoPawnTurrent, All, All);

// forward declarations
class UInputComponent;
class AJeJoPawnTank;

/*!
 * 
 */
UCLASS()
class TOONTANKSGAME_API AJeJoPawnTurrent : public AJeJoPawnBase
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AJeJoPawnTurrent() noexcept;

	// Called every frame
	void Tick(float deltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "JJPawnTurrent")
	float GetDistanceToPlayer() const noexcept;

protected:
	// Called when the game starts or when spawned
	void BeginPlay() override;

	void Fire_Implementation() noexcept override;
	void HandleDestruction_Implementation() noexcept override;

private:
	FTimerHandle fireRateTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JJPawnTurrent", meta = (AllowPrivateAccess = "true"))
	float fireRate{ 2.f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JJPawnTurrent", meta = (AllowPrivateAccess = "true"))
	float distanceRange{ 1000.f };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "JJPawnTurrent", meta = (AllowPrivateAccess = "true"))
	AJeJoPawnTank* playerPawn{ nullptr };

	void CheckFireCondition() noexcept;
};

