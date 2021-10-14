// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    PrintLine(TEXT("Welcome to Bull Cows!"));
    PrintLine(TEXT("Guess the 5 letter word!")); //Hard coded number, Remove it
    PrintLine(TEXT("Type in a guess!"));
    PrintLine(TEXT("Press enter to continue!"));

}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();
    FString HiddenWord = TEXT("muted"); //move this outside of function so it doesnt keep being recalled
    if (Input == HiddenWord) { // == is case insensitive, .Equals is case sensitive
        PrintLine(Input + TEXT(" is the hidden word!"));
    }
    else {
        PrintLine(Input + TEXT(" is not the hidden word. Try again!"));
    }
}