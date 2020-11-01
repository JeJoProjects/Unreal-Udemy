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

class UInputComponent;

UCLASS()
class TOONTANKSGAME_API AJeJoPawnBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AJeJoPawnBase();	

	// Called every frame
	void Tick(float deltaTime) override;

	// Called to bind functionality to input
	void SetupPlayerInputComponent(UInputComponent* playerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	void BeginPlay() override;

private:

};

