/****************************************************************************************
 * ------------------------
 *
 * @Authur : JeJo
 * @license: MIT
****************************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "JeJoPawnBase.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogJeJoPawnBase, All, All);

// forward declarations
class UInputComponent;
class UCapsuleComponent;
class UStaticMeshComponent;
class USceneComponent;

UCLASS()
class TOONTANKSGAME_API AJeJoPawnBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AJeJoPawnBase() noexcept;	

	// Called every frame
	void Tick(float deltaTime) override;

	// Called to bind functionality to input
	void SetupPlayerInputComponent(UInputComponent* playerInputComp) override;

protected:
	UFUNCTION(BlueprintNativeEvent, Category = "JJPawnBase")
	void RotateTurrent(const FVector& lookAtTarget);
	virtual void RotateTurrent_Implementation(const FVector& targetMesh) noexcept;

	UFUNCTION(BlueprintNativeEvent, Category = "JJPawnBase")
	void Fire();
	virtual void Fire_Implementation() noexcept;

	UFUNCTION(BlueprintNativeEvent, Category = "JJPawnBase")
	void HandleDestruction();
	virtual void HandleDestruction_Implementation() noexcept;

	// Called when the game starts or when spawned
	void BeginPlay() override;

	virtual void CheckComponets() const noexcept;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "JJPawnBase", meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* capsuleComp{ nullptr };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "JJPawnBase", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* baseStaticMeshComp{ nullptr };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "JJPawnBase", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* turrentStaticMeshComp{ nullptr };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "JJPawnBase", meta = (AllowPrivateAccess = "true"))
	USceneComponent* projectileSpawnPointComp{ nullptr };
};

