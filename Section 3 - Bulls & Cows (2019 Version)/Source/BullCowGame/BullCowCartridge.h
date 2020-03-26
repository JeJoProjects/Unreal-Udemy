// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <utility> // std::pair

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
	void GetValidWords() const noexcept;
	void SetupGame() noexcept;
	bool IsIsogram(const FString &) const noexcept;
	void LostMessage(const FString &) noexcept;
	std::pair<int32, int32> GetBullsCows(const FString &) const noexcept;
	void ProcessGuess(const FString &) noexcept;
	void EndGame() noexcept;

private:
	FString HiddenWord;
	int32 Lives;
	bool bGameOver;
};
