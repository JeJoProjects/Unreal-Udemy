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
	// Called when the game starts or when spawned
	void BeginPlay() override;

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

