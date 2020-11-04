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

/*!
 * 
 */
UCLASS()
class TOONTANKSGAME_API AJeJoPawnTank : public AJeJoPawnBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JJPawnTank")
	float moveSpeed{ 100.f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JJPawnTank")
	float rotateSpeed{ 100.f };

	// Sets default values for this pawn's properties
	AJeJoPawnTank() noexcept;

	// Called every frame
	void Tick(float deltaTime) override;

	// Called to bind functionality to input
	void SetupPlayerInputComponent(UInputComponent* playerInputComp) override;

protected:
	// Called when the game starts or when spawned
	void BeginPlay() override;

private:

	FVector moveDirection;
	FQuat rotationDirection;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "JJPawnTank", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* springArmComp{ nullptr };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "JJPawnTank", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* cameraComp{ nullptr };

	void CalculateMoveInput(const float value) noexcept;

	void CalculateRotationInput(const float value) noexcept;

	void Move() noexcept;

	void Rotate() noexcept;
};
