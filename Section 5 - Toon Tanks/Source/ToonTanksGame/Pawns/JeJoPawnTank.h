/****************************************************************************************
 * ------------------------
 *
 * @Authur : JeJo
 * @license: MIT
****************************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "JeJoPawnBase.h"
#include "JeJoPawnTank.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogJeJoPawnTank, All, All);

// forward declarations
class UInputComponent;
class UCameraComponent;
class USpringArmComponent;
class APlayerController;

/*!
 * 
 */
UCLASS()
class TOONTANKSGAME_API AJeJoPawnTank : public AJeJoPawnBase
{
	GENERATED_BODY()

public:

	// Sets default values for this pawn's properties
	AJeJoPawnTank() noexcept;

	// Called every frame
	void Tick(float deltaTime) override;

	// Called to bind functionality to input
	void SetupPlayerInputComponent(UInputComponent* playerInputComp) override;

protected:
	// Called when the game starts or when spawned
	void BeginPlay() override;

	void CheckComponets() const noexcept override;
	void Fire_Implementation() const override;
	void HandleDestruction_Implementation() noexcept override;

private:
	FVector moveDirection;
	FQuat rotationDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JJPawnTank", meta = (AllowPrivateAccess = "true"))
	float rotateSpeed{ 200.f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JJPawnTank", meta = (AllowPrivateAccess = "true"))
	float moveSpeed{ 600.f };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "JJPawnTank", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* springArmComp{ nullptr };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "JJPawnTank", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* cameraComp{ nullptr };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "JJPawnTank", meta = (AllowPrivateAccess = "true"))
	APlayerController* playerController{ nullptr };

	void CalculateMoveInput(const float value) noexcept;

	void CalculateRotationInput(const float value) noexcept;

	void Move() noexcept;

	void Rotate() noexcept;
};
