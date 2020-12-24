// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() { // When the game starts 
    
    Super::BeginPlay();

    const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordLists/HiddenWordList.txt");
    //FFileHelper::LoadFileToStringArray(Words, *WordListPath);

    FFileHelper::LoadFileToStringArrayWithPredicate(Words, *WordListPath, [](const FString& Word) {return Word.Len() > 4 && IsIsogram(Word) && Word.Len() < 8; });

    //Words = GetValidWords();
    SetUpGame();

    PrintLine(TEXT("The number of possible words is %i"), Words.Num());
    PrintLine(TEXT("The HiddenWord is: %s. \nIt is a %i long word."), *HiddenWord, HiddenWord.Len()); // Debug Line

}

void UBullCowCartridge::OnInput(const FString& Input) { // When the player hits enter    

    if (bGameOver) {
        ClearScreen();
        SetUpGame();
    }
    else {
        ProcessGuess(Input);
    }
}

void UBullCowCartridge::SetUpGame() {
    PrintLine(TEXT("Welcome to Bull Cows!"));
    
    //HiddenWord = GetValidWords()[FMath::RandRange(0,Words.Num()-1)];
    HiddenWord = Words[FMath::RandRange(0, Words.Num()-1)];
    Lives = HiddenWord.Len();
    bGameOver = false;

    PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len());
    PrintLine(TEXT("You have %i lives"), Lives);
    PrintLine(TEXT("Press enter to continue..."));

}

void UBullCowCartridge::EndGame() {
    bGameOver = true;
    PrintLine(TEXT("\nPress enter to play again"));
}

void UBullCowCartridge::ProcessGuess(const FString& Guess) {
    
    if (Guess == HiddenWord) {
        PrintLine(TEXT("You Won!"));
        EndGame();
        return;
    }


    if (HiddenWord.Len() != Guess.Len()) {
        PrintLine(TEXT("The hidden word is %i letters long"), HiddenWord.Len());
        PrintLine(TEXT("Sorry, wrong length, try guessing again! \nYou have %i lives remaining"), Lives);
        return;
    }


    if (!IsIsogram(Guess)) {
        PrintLine(TEXT("No repeating letters, guess again"));
        return;
    }

    PrintLine(TEXT("Lost a life!"));
    Lives--;

    if (Lives <= 0) {
        ClearScreen();
        PrintLine(TEXT("You have no lives left!"));
        PrintLine(TEXT("The hidden word is %s"), *HiddenWord);
        EndGame();
        return;
    }

    
    // Show the player Bulls and Cows
    FBullCowCount res = GetBullCows(Guess);


    PrintLine(TEXT("You have %i Bulls and %i Cows"), res.Bulls, res.Cows);
       
    PrintLine(TEXT("Guess again, you have %i lives left"), Lives);
}

bool UBullCowCartridge::IsIsogram(const FString& Word) {

    for (int32 Index = 0; Index < Word.Len() - 1; Index++) {
        for (int32 Comparison = Index + 1; Comparison < Word.Len(); Comparison++) {
            if (Word[Index] == Word[Comparison]) {
                return false;
            }
        }
    }

    return true;
}


TArray<FString> UBullCowCartridge::GetValidWords() const {
    TArray<FString> ValidWords;

    for (FString Word : Words) {
        if (Word.Len() >= 4 && Word.Len() <= 8 && IsIsogram(Word)) {
            ValidWords.Emplace(Word);
        }
    }

    return ValidWords;
}


FBullCowCount UBullCowCartridge::GetBullCows(const FString& Guess) const{
    FBullCowCount Count;

    for (int32 Index = 0; Index < Guess.Len(); Index++) {
        if (Guess[Index] == HiddenWord[Index]) {
            Count.Bulls++;
            continue;
        }   

        for (int32 HiddenIndex = 0; HiddenIndex < HiddenWord.Len(); HiddenIndex++) {
            if (Guess[Index] == HiddenWord[HiddenIndex]) {
                Count.Cows++;
                break;
            }
        }
    }

    return Count;
}

