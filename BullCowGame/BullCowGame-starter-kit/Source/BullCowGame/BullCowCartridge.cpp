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
        if (Input == HiddenWord) {
            PrintLine(TEXT("You Won!"));
            EndGame();
        }
        else {
            if (--Lives > 0) {
                if (HiddenWord.Len() != Input.Len()) {
                    PrintLine(TEXT("Sorry, wrong length, try guessing again! \nYou have %i lives remaining"), Lives);
                }
                else {
                    PrintLine(TEXT("Sorry, same length, try guessing again! \nYou have %i lives remaining"), Lives);
                }
            }
            else {
                PrintLine(TEXT("You have no lives left!"));
                EndGame();
            }
        }
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
}

void UBullCowCartridge::EndGame() {
    bGameOver = true;
    PrintLine(TEXT("Press enter to play again"));
}

