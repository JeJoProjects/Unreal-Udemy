// Fill out your copyright notice in the Description page of Project Settings.


#include "JeJoGrabber.h"

DEFINE_LOG_CATEGORY(LogJeJoGrabber)

void UJeJoGrabber::BeginPlay()
{
	Super::BeginPlay();
}

UJeJoGrabber::UJeJoGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  
	// You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


void UJeJoGrabber::TickComponent(
	float deltaTime, ELevelTick tickType, FActorComponentTickFunction* thisTickFunction)
{
	Super::TickComponent(deltaTime, tickType, thisTickFunction);
	
}

