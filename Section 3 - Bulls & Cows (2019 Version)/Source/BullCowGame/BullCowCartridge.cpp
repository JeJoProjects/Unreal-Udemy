// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    PrintLine(TEXT("Welcome to Bull Cows Game!"));
    PrintLine(TEXT("Press enter to continue..."));
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();
    // PrintLine(Input);
    const FString HiddenWorld{TEXT("let")};

    if(HiddenWorld == Input)
    {
        PrintLine(TEXT("!!! Congratz !!!\n You won!..."));
    }
    else
    {
        PrintLine(TEXT("You lost!..."));
    }
}