// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() { // When the game starts 
    
    Super::BeginPlay();

    SetUpGame();

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
    
    HiddenWord = TEXT("BREAD");
    Lives = HiddenWord.Len();
    bGameOver = false;

    PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len());
    PrintLine(TEXT("You have %i lives"), Lives);
    PrintLine(TEXT("Press enter to continue..."));

    //const TCHAR HW[] = TEXT("BREAD");
    //PrintLine(TEXT("Character 1 of the hidden word is: %c"), HiddenWord[0]);
    //PrintLine(TEXT("Character 4 of the HW is: %c"), HW[4]);
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
       
    PrintLine(TEXT("Guess again, you have %i lives left"), Lives);
}

bool UBullCowCartridge::IsIsogram(const FString& Word) const {

    for (int32 Index = 0; Index < Word.Len(); Index++) {
        PrintLine(TEXT("%c"), Word[Index]);
    }

    return true;
}

