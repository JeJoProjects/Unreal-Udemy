// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

public:
	void BeginPlay() override;
	void OnInput(const FString &) override;

private:
	void SetupGame() noexcept;
	bool IsIsogram(const FString &) const noexcept;
	void LostMessage() noexcept;
	void ProcessGuess(const FString &) noexcept;
	void EndGame() noexcept;

private:
	FString HiddenWorld;
	int32 Lives;
	bool bGameOver;
};
