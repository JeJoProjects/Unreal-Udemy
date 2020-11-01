// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/JeJoPawnBase.h"

// Sets default values
AJeJoPawnBase::AJeJoPawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AJeJoPawnBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AJeJoPawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AJeJoPawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

