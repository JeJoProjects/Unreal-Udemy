/****************************************************************************************
 * ------------------------
 *
 * @Authur : JeJo
 * @license: MIT
****************************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JeJoProjectileBase.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogJeJoProjectileBase, All, All);

// forward declarations
class UProjectileMovementComponent;
class UStaticMeshComponent;
class DamageType;

UCLASS()
class TOONTANKSGAME_API AJeJoProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJeJoProjectileBase() noexcept;


	void Tick(float DeltaTime) override;

protected:
	void BeginPlay() override;
	virtual void SetupComponets() noexcept;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JJProjectileBase", meta = (AllowPrivateAccess = "true"))
	float movementSpeed{ 1300.f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JJProjectileBase", meta = (AllowPrivateAccess = "true"))
	float damage{ 50.f };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "JJPawnBase", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* projectileStaticMeshComp{ nullptr };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "JJProjectileBase", meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* projectileMovementComp{ nullptr };

	UPROPERTY(EditDefaultsOnly, Category = "JJProjectileBase")
	TSubclassOf<UDamageType> damageType{ nullptr };

};
