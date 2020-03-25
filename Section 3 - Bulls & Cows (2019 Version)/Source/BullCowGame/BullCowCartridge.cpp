// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordsList.h"

#include <map>
#include <cstddef>     // std::size_t
#include <type_traits> // std::decay_t

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    // setting up the Game
    SetupGame();
}

void UBullCowCartridge::OnInput(const FString &Input) // When the player hits enter
{

    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
    else // else checking the player guess.
    {
        ProcessGuess(Input);
    }
}

void UBullCowCartridge::SetupGame() noexcept
{
    // welcoming the player
    PrintLine(TEXT("Welcome to Bull Cows Game!"));

    HiddenWorld = TEXT("let");
    Lives = 4;
    bGameOver = false;

    PrintLine(TEXT("Guess the %i letter word!"), HiddenWorld.Len());
    PrintLine(TEXT("You have %i lives."), Lives);
    PrintLine(TEXT("Type in your guess and \npress enter to continue..."));
}

bool UBullCowCartridge::IsIsogram(const FString &UserGuess) const noexcept
{
    using ElementType = std::decay_t<decltype(*UserGuess.begin())>;
    std::map<ElementType, std::size_t> CharMap;
    for(const ElementType element: UserGuess)
    {
        CharMap[element]++;
        if(CharMap[element] > 1u)
            return false;
    }
    return true;
}

void UBullCowCartridge::LostMessage() noexcept
{
    PrintLine(TEXT("You lost a life!"));
    PrintLine(TEXT("You have %i lives remaining"), --Lives);
    PrintLine(TEXT("Try guess again..."));
}

void UBullCowCartridge::ProcessGuess(const FString &UserGuess) noexcept
{
    // matching case
    if (UserGuess == HiddenWorld)
    {
        ClearScreen();
        PrintLine(TEXT("!!! Congrats !!!\n You have won!..."));
        EndGame();
        return; // done here!
    }

    // checking the length
    if (UserGuess.Len() != HiddenWorld.Len())
    {
        ClearScreen();
        PrintLine(TEXT("The hidden word is %i charectors long."), HiddenWorld.Len());
        LostMessage();
        return; // done here!
    }

    // check if Isogram
    if (!IsIsogram(UserGuess))
    {
        ClearScreen();
        PrintLine(TEXT("No repeating letters, guess again!"));
        LostMessage();
        return; // done here!
    }

    // decrement the lives and validate
    if (--Lives <= 0)
    {
        ClearScreen();
        PrintLine(TEXT("You have no lives left!"));
        PrintLine(TEXT("The hidden word was: %s"), *HiddenWorld);
        EndGame();
        return; // done here!
    }
}

void UBullCowCartridge::EndGame() noexcept
{
    bGameOver = true;
    PrintLine(TEXT("\nPress enter to play again!..."));
}
