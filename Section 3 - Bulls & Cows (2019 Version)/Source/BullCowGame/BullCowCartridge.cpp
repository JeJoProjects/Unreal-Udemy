// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordsList.h"

#include <map>
#include <algorithm>   // std::find
#include <type_traits> // std::decay_t

static TArray<FString> ValidArray;

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
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

void UBullCowCartridge::GetValidWords() const noexcept
{
    // fillter out the valid words
    for (const FString &word : Words)
        if (word.Len() >= 4 && word.Len() <= 8 && this->IsIsogram(word))
            ValidArray.Emplace(word);
}

void UBullCowCartridge::SetupGame() noexcept
{
    GetValidWords();
    // welcoming the player
    PrintLine(TEXT("Welcome to Bull Cows Game!"));

    // intilizting the members
    HiddenWord = ValidArray[FMath::RandRange(0, ValidArray.Num() - 1)];
    Lives = HiddenWord.Len();
    bGameOver = false;

    PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len());
    // PrintLine(TEXT("The HiddenWord is: %s"), *HiddenWord); // Debug message

    PrintLine(TEXT("You have %i lives."), Lives);
    PrintLine(TEXT("Type in your guess and \npress enter to continue..."));
}

bool UBullCowCartridge::IsIsogram(const FString &UserGuess) const noexcept
{
    using ElementType = std::decay_t<decltype(*UserGuess.begin())>;
    std::map<ElementType, int32> CharMap;
    for (const ElementType element : UserGuess)
    {
        CharMap[element]++;
        if (CharMap[element] > 1)
            return false;
    }
    return true;
}

void UBullCowCartridge::LostMessage(const FString &UserGuess) noexcept
{
    const auto [Bulls, Cows] = GetBullsCows(UserGuess);
    PrintLine(TEXT("You have %i Bulls and %i Cows."), Bulls, Cows);
    // decrement the lives and validate
    if (--Lives <= 0)
    {
        PrintLine(TEXT("You have no lives left!"));
        PrintLine(TEXT("The hidden word was: %s"), *HiddenWord);
        EndGame();
        return; // done here!
    }

    PrintLine(TEXT("You lost a life!"));
    PrintLine(TEXT("You have %i lives remaining"), Lives);
    PrintLine(TEXT("Try guess again..."));
}

std::pair<int32, int32>
UBullCowCartridge::GetBullsCows(const FString &UserGuess) const noexcept
{
    int32 BullsCount{0}, CowsCount{0};

    for (int32 GuessIdx{0}; GuessIdx < UserGuess.Len(); ++GuessIdx)
    {
        if (UserGuess[GuessIdx] == HiddenWord[GuessIdx])
        {
            ++BullsCount;
            continue;
        }

        int32 Index{0};
        if (HiddenWord.FindChar(UserGuess[GuessIdx], Index))
            ++CowsCount;
    }
    return {BullsCount, CowsCount};
}

void UBullCowCartridge::ProcessGuess(const FString &UserGuess) noexcept
{
    // matching case
    if (UserGuess == HiddenWord)
    {
        ClearScreen();
        PrintLine(TEXT("!!! Congrats !!!\n You have won!..."));
        EndGame();
        return; // done here!
    }

    // checking the length
    if (UserGuess.Len() != HiddenWord.Len())
    {
        ClearScreen();
        PrintLine(TEXT("The hidden word is %i charectors long."), HiddenWord.Len());
        LostMessage(UserGuess);
        return; // done here!
    }

    // check if Isogram
    if (!IsIsogram(UserGuess))
    {
        ClearScreen();
        PrintLine(TEXT("No repeating letters, guess again!"));
        LostMessage(UserGuess);
        return; // done here!
    }

    // last case
    ClearScreen();
    LostMessage(UserGuess);
}

void UBullCowCartridge::EndGame() noexcept
{
    bGameOver = true;
    PrintLine(TEXT("\nPress enter to play again!..."));
}
